#ifndef _CYCLE_BUFFER_H
#define _CYCLE_BUFFER_H

#include <stdint.h>

#define CYCLE_BUFFER_SIZE 100

typedef int buffer_elem_t;

typedef struct cyc_buffer {
  uint16_t position;
  buffer_elem_t content[CYCLE_BUFFER_SIZE];
} cyc_buffer_t;

void cycbuffer_init(cyc_buffer_t* buffer);
void cycbuffer_destroy(cyc_buffer_t* buffer);

int cycbuffer_get_element(const cyc_buffer_t* buffer, uint16_t offset,
                          buffer_elem_t* value);
void cycbuffer_store_element(cyc_buffer_t* buffer, buffer_elem_t value);

#endif  //_CYCLE_BUFFER_H
