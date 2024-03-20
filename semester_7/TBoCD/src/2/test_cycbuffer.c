#include <stdio.h>

#include "buffer.h"

int main(void) {
  cyc_buffer_t buffer;
  cycbuffer_init(&buffer);

  cycbuffer_store_element(&buffer, 48);
  cycbuffer_store_element(&buffer, 53);
  cycbuffer_store_element(&buffer, 89);

  int exec_ret;
  int value_int;

  exec_ret = cycbuffer_get_element(&buffer, 0, &value_int);
  printf("%d (ret=%d)\n", value_int, exec_ret);
  exec_ret = cycbuffer_get_element(&buffer, 1, &value_int);
  printf("%d (ret=%d)\n", value_int, exec_ret);
  exec_ret = cycbuffer_get_element(&buffer, 2, &value_int);
  printf("%d (ret=%d)\n", value_int, exec_ret);

  cycbuffer_destroy(&buffer);
}
