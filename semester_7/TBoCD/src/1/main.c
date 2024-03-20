#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define INVALID_WAY ((uint32_t)-1)

typedef enum { LITERAL_A, LITERAL_B, LITERAL_C } literal_t;

typedef struct exec_ctx {
  FILE* instream;
} exec_ctx_t;

static bool _is_terminate_state(uint32_t state) {
  return (1 == state) || (2 == state) || (3 == state) || (7 == state) ||
         (9 == state) || (10 == state);
}

static int _exec_program(exec_ctx_t* ctx) {
  static uint32_t _table[][11] = {
      [LITERAL_A] = {INVALID_WAY, 2, 2, INVALID_WAY, 5, 5, 5, INVALID_WAY, 10,
                     INVALID_WAY, INVALID_WAY},
      [LITERAL_B] = {4, 3, INVALID_WAY, 3, INVALID_WAY, INVALID_WAY,
                     INVALID_WAY, 8, 9, 8, 8},
      [LITERAL_C] = {1, INVALID_WAY, INVALID_WAY, INVALID_WAY, 7, 6, 7,
                     INVALID_WAY, INVALID_WAY, INVALID_WAY, INVALID_WAY}};

  bool terminate = false, has_error = false;
  uint32_t step_counter = 0;
  uint32_t state = 0;
  uint32_t terminal;

  while (!terminate && !has_error) {
    int symb = fgetc(ctx->instream);
    ++step_counter;

    switch (symb) {
      case 'a':
      case 'A':
        terminal = LITERAL_A;
        break;
      case 'b':
      case 'B':
        terminal = LITERAL_B;
        break;
      case 'c':
      case 'C':
        terminal = LITERAL_C;
        break;
      case EOF:
        if (_is_terminate_state(state)) {
          terminate = true;
        } else {
          fprintf(stderr, "Неожиданный конец файла. Выход.\n");
          has_error = true;
        }
        break;

      default:
        if (isspace(symb)) {
          continue;
        } else {
          fprintf(stderr, "Найден неожиданный символ: %c. Выход.\n", symb);
          has_error = true;
        }
        break;
    }

    if (!(terminate || has_error)) {
      state = _table[terminal][state];
      if (state == INVALID_WAY) {
        fprintf(stderr, "Неожиданный переход в позиции %u. Выход.\n",
                step_counter);
        has_error = true;
      } else {
      }
    } else {
    }
  }

  return has_error ? 1 : 0;
}

static inline void _parse_args(int argc, char** argv, exec_ctx_t* ctx,
                               bool* parse_err) {
  *parse_err = false;
  if (1 == argc) {
    ctx->instream = stdout;
  } else {
    FILE* file = fopen(argv[1], "r");
    if (NULL == file) {
      fprintf(stderr, "%s: неудалось открыть для чтения.\n", argv[1]);
      *parse_err = true;
    } else {
      ctx->instream = file;
    }
  }
}

int main(int argc, char** argv) {
  bool parse_error = false;
  exec_ctx_t ctx;
  _parse_args(argc, argv, &ctx, &parse_error);

  int ret = 0;
  if (parse_error) {
    ret = 1;
  } else {
    ret = _exec_program(&ctx);
  }

  if (0 == ret) {
    printf("Программа успешно завершена.\n");
  }

  return ret;
}