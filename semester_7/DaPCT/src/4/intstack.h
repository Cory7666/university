#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _INTSTACK_H
#define _INTSTACK_H

typedef int32_t intstack_elem_t;

#define INTSTACK_MAX_SIZE 16

typedef struct intstack {
  intstack_elem_t values[INTSTACK_MAX_SIZE];
  size_t count;
} intstack_t;

void intstack_append(intstack_t* self, intstack_elem_t values);
intstack_elem_t intstack_pop(intstack_t* self);
size_t intstack_count(const intstack_t* self);
bool intstack_is_empty(const intstack_t* self);

#endif
