#ifndef _SYNTAX_ANALYZER_PVT_H
#define _SYNTAX_ANALYZER_PVT_H

#include <stdbool.h>
#include <stddef.h>

#include "buffer.h"

typedef enum state_liter {
  LITER_F = 0,
  LITER_O,
  LITER_R,
  LITER_T,
  LITER_ANY_SYMBOL,
  LITER_NON_ZERO_DIGIT,
  LITER_ZERO,
  LITER_SIGN_PLUS,
  LITER_SIGN_MINUS,
  LITER_OPEN_BRACE,
  LITER_CLOSE_BRACE,
  LITER_SIGN_EQUAL,
  LITER_SEMICOLON,
  LITER_STAR,
  LITER_DIVIDE,
  LITER_DOT,
  LITER_SPACE,
  LITER_INCORRECT_SYMBOL,
  LITER_MAX_CODE
} state_liter_t;

typedef enum end_state {
  // Обычные конечные состояния анализа
  END_STATE_START = 100,
  END_WORD_FOR,
  END_WORD_TO,
  END_IDENTIFIER,
  END_CONST,
  END_OPEN_BRACE,
  END_CLOSE_BRACE,
  END_ASSIGN,
  END_SEMICOLON,
  END_STAR,
  END_SLASH,

  // Ошибки выполнения синтаксического анализа
  END_ERRORS_START,
  END_SYNTAX_ERROR,
  END_IDENT_FORMAT_ERROR,
  END_MISSING_FRAC_PART_ERROR,

  // Ошибки выполнения анализа (динамические ошибки)
  END_TOO_LONG_FLOAT_ERROR
} end_state_t;

/// @brief Структура, содержащая информацию о позиционировании
/// указателя в файле
typedef struct file_pos {
  size_t line;
  size_t col;
} file_pos_t;

typedef struct float_desc {
  size_t integral_size;
  size_t frac_size;
} float_desc_t;

extern int _analyzer_next_state(state_liter_t liter, int state);
static state_liter_t _analyzer_get_alpha_type(int symbol);
static state_liter_t _analyzer_get_liter_type_for_special_symbol(int symbol);
static void _file_pos_new_line(file_pos_t* obj);
static void _file_pos_inc(file_pos_t* obj);
static void _float_desc_reset(float_desc_t* obj);
static bool _float_desc_is_in_bounds(const float_desc_t* obj);
static void _slice_buffer(char* dest, const cyc_buffer_t* buffer,
                          uint16_t start_offset, uint16_t end_offset);
static void _print_syntax_error(const cyc_buffer_t* buffer, int error_state,
                                const file_pos_t* filepos);
static const char* _error_state_to_string(int state);

#endif  //_SYNTAX_ANALYZER_PVT_H
