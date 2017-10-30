#include "cob.h"

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdarg.h>

void * new(const void * _class, ...)
{
  const struct AbstractClass * class = _class;
  void * p = calloc(1, class->size);

  assert(p);

  // Initialize the class field of the struct
  *(const struct AbstractClass **) p = class;

  if (class->constructor) {
    va_list args;
    va_start(args, _class);
    p = class->constructor(p, &args);
    va_end(args);
  }

  return p;
}

void delete(void * self) {
  const struct AbstractClass ** class = self;
  if (self && * class && (*class)->destructor) {
    self = (*class)->destructor(self);
  }
  free(self);
}
