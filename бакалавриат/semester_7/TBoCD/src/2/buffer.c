#include "buffer.h"

#include <string.h>

void cycbuffer_init(cyc_buffer_t* buffer) {
  buffer->position = 0;
  memset(buffer->content, 0, CYCLE_BUFFER_SIZE * sizeof(buffer_elem_t));
}

void cycbuffer_destroy(cyc_buffer_t* buffer) {}

int cycbuffer_get_element(const cyc_buffer_t* buffer, uint16_t offset,
                          buffer_elem_t* value) {
  int ret = 0;
  const uint16_t offset_plus_one = offset + 1;

  if (offset >= CYCLE_BUFFER_SIZE) {
    ret = 1;
  } else {
    if (offset_plus_one > buffer->position) {
      const uint16_t idx =
          ((uint16_t)CYCLE_BUFFER_SIZE) - (offset_plus_one - buffer->position);
      *value = buffer->content[idx];
    } else {
      *value = buffer->content[buffer->position - offset_plus_one];
    }
    ret = 0;
  }
  return ret;
}

void cycbuffer_store_element(cyc_buffer_t* buffer, buffer_elem_t value) {
  if (CYCLE_BUFFER_SIZE == buffer->position) {
    buffer->position = 0;
  } else {
  }
  buffer->content[buffer->position] = value;
  ++buffer->position;
}
