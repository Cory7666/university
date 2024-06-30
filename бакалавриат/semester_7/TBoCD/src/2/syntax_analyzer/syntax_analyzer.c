#include "syntax_analyzer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "syntax_analyzer.pvt.h"

void analyze(FILE* istream) {
  int symbol;
  int current_state = 0;
  state_liter_t liter;
  bool loop_exit_flag = false;
  file_pos_t file_pos = {0};

  cyc_buffer_t iobuffer;
  cycbuffer_init(&iobuffer);

  bool is_scanning_float = false;
  float_desc_t float_desc;

  while (!loop_exit_flag) {
    cycbuffer_store_element(&iobuffer, getc(istream));
    cycbuffer_get_element(&iobuffer, 0, &symbol);

    if (EOF == symbol) {
      puts("Достигнут конец файла.");
      break;
    } else if (isalpha(symbol) || ('_' == symbol)) {
      liter = _analyzer_get_alpha_type(symbol);
    } else if (isdigit(symbol)) {
      liter = ('0' == symbol) ? LITER_ZERO : LITER_NON_ZERO_DIGIT;
    } else {
      liter = _analyzer_get_liter_type_for_special_symbol(symbol);
    }

    current_state = _analyzer_next_state(liter, current_state);

    if (END_STATE_START < current_state) {
      printf("At l%lu:c%lu - END STATE: %d. Reset to state 0.\n", file_pos.line,
             file_pos.col, current_state);
      if (END_ERRORS_START < current_state) {
        _print_syntax_error(&iobuffer, current_state, &file_pos);
      } else if (is_scanning_float && !_float_desc_is_in_bounds(&float_desc)) {
        _print_syntax_error(&iobuffer, END_TOO_LONG_FLOAT_ERROR, &file_pos);
      } else {
      }
      current_state = 0;
      is_scanning_float = false;
    } else {
      if (!is_scanning_float && (12 == current_state)) {
        is_scanning_float = true;
        _float_desc_reset(&float_desc);
      }

      // Отдельная обработка чисел с плавающей точкой
      if (is_scanning_float) {
        if (12 == current_state) {
          // Увеличение счётчика целой части
          ++float_desc.integral_size;
        } else if ((14 == current_state) || (15 == current_state)) {
          // Увеличение счётчика дробной части
          ++float_desc.frac_size;
        } else {
          // Вероятнее всего, сейчас была обработана точка
        }
      }
    }

    if ('\n' == symbol) {
      _file_pos_new_line(&file_pos);
    } else {
      _file_pos_inc(&file_pos);
    }
  }

  cycbuffer_destroy(&iobuffer);
}

static state_liter_t _analyzer_get_alpha_type(int symbol) {
  state_liter_t ret;

  switch (toupper(symbol)) {
    case 'F':
      ret = LITER_F;
      break;
    case 'O':
      ret = LITER_O;
      break;
    case 'R':
      ret = LITER_R;
      break;
    case 'T':
      ret = LITER_T;
      break;
    default:
      ret = LITER_ANY_SYMBOL;
      break;
  }

  return ret;
}

static state_liter_t _analyzer_get_liter_type_for_special_symbol(int symbol) {
  state_liter_t ret;

  switch (symbol) {
    case '+':
      ret = LITER_SIGN_PLUS;
      break;
    case '-':
      ret = LITER_SIGN_MINUS;
      break;
    case '(':
      ret = LITER_OPEN_BRACE;
      break;
    case ')':
      ret = LITER_CLOSE_BRACE;
      break;
    case '=':
      ret = LITER_SIGN_EQUAL;
      break;
    case ';':
      ret = LITER_SEMICOLON;
      break;
    case '*':
      ret = LITER_STAR;
      break;
    case '/':
      ret = LITER_DIVIDE;
      break;
    case '.':
      ret = LITER_DOT;
      break;
    default:
      ret = isspace(symbol) ? LITER_SPACE : LITER_INCORRECT_SYMBOL;
      break;
  }

  return ret;
}

static void _file_pos_new_line(file_pos_t* obj) {
  ++obj->line;
  obj->col = 0;
}

static void _file_pos_inc(file_pos_t* obj) { ++obj->col; }

static void _float_desc_reset(float_desc_t* obj) {
  obj->integral_size = 0;
  obj->frac_size = 0;
}

static bool _float_desc_is_in_bounds(const float_desc_t* obj) {
  return (obj->integral_size <= ANALYZER_FLOAT_MAX_INTEGRAL_SIZE) &&
         (obj->integral_size > 0) && (obj->frac_size > 0) &&
         (obj->frac_size <= ANALYZER_FLOAT_MAX_FRAC_SIZE);
}

static void _slice_buffer(char* dest, const cyc_buffer_t* buffer,
                          uint16_t start_offset, uint16_t end_offset) {
  uint16_t real_start_offset = start_offset;
  bool loop_exit_flag = false;
  buffer_elem_t symbol;

  while (!loop_exit_flag) {
    cycbuffer_get_element(buffer, real_start_offset, &symbol);

    if (0 == symbol) {
      --real_start_offset;
      if (real_start_offset == end_offset) {
        loop_exit_flag = true;
      }
    } else {
      loop_exit_flag = true;
    }
  }

  uint16_t dst_idx = 0;
  for (uint16_t idx = real_start_offset; idx >= end_offset; --idx) {
    cycbuffer_get_element(buffer, idx, &symbol);
    dest[dst_idx] = ('\n' == symbol) ? ' ' : (char)symbol;
    ++dst_idx;

    if (idx == end_offset) {
      break;
    }
  }
  dest[dst_idx] = '\0';
}

static const char* _error_state_to_string(int state) {
  const char* ret = NULL;

  if (state <= END_ERRORS_START) {
    ret = "Не ошибка.";
  } else {
    switch (state) {
      case END_SYNTAX_ERROR:
        ret = "Синтаксическая ошибка.";
        break;
      case END_IDENT_FORMAT_ERROR:
        ret = "Неверное имя идентификатора.";
        break;
      case END_MISSING_FRAC_PART_ERROR:
        ret = "У константы должна быть дробная часть.";
        break;
      case END_TOO_LONG_FLOAT_ERROR:
        ret = "Заданная константа не соответствует требуемым размерам.";
        break;
      default:
        ret = "Неизвестная ошибка.";
        break;
    }
  }

  return ret;
}

static void _print_syntax_error(const cyc_buffer_t* buffer, int error_state,
                                const file_pos_t* filepos) {
  char slice_buff[1024];
  int underline_start = 1;

  _slice_buffer(slice_buff, buffer, 10, 0);

  const size_t pre_underline_len = strlen(slice_buff) - 2;

  printf("ERROR: %s\n", _error_state_to_string(error_state));
  printf("At l%lu:c%lu: %n%s\n", filepos->line, filepos->col, &underline_start,
         slice_buff);
  printf("%*c", underline_start, ' ');

  for (int cntr = 0; cntr < pre_underline_len; ++cntr) {
    putc('~', stdout);
  }

  putc('^', stdout);
  putc('~', stdout);
  putc('\n', stdout);
}
