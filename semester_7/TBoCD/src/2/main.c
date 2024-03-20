#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "syntax_analyzer.h"

typedef struct exec_ctx {
  FILE* istream;
} exec_ctx_t;

static int _parse_args(int argc, char** argv, exec_ctx_t* ctx) {
  int ret = 0;
  if (1 == argc) {
    ctx->istream = stdin;
  } else {
    FILE* file = fopen(argv[1], "r");
    if (NULL == file) {
      ret = 1;
    } else {
      ctx->istream = file;
    }
  }

  return ret;
}

static void _destroy_context(exec_ctx_t* ctx) {
  if ((stdin != ctx->istream) && (NULL != ctx->istream)) {
    fclose(ctx->istream);
    ctx->istream = NULL;
  }
}

static void _analyze(exec_ctx_t* ctx) { analyze(ctx->istream); }

int main(int argc, char** argv) {
  exec_ctx_t ctx;
  int parse_ret = _parse_args(argc, argv, &ctx);

  if (0 == parse_ret) {
    _analyze(&ctx);
  } else {
    fputs("Ошибка парсинга аргументов.", stderr);
  }
  _destroy_context(&ctx);
}
