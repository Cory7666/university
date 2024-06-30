#include "intstack.h"

void intstack_append(intstack_t* self, intstack_elem_t values) {
  if ((NULL != self) && (INTSTACK_MAX_SIZE - 1 > self->count)) {
    self->values[self->count++] = values;
  }
}

intstack_elem_t intstack_pop(intstack_t* self) {
  intstack_elem_t ret = 0;
  if ((NULL != self) && (0 < self->count)) {
    --self->count;
    ret = self->values[self->count];
  }
  return ret;
}

size_t intstack_count(const intstack_t* self) { return self->count; }

bool intstack_is_empty(const intstack_t* self) {
  return intstack_count(self) > 0;
}
