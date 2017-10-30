#include "mem.h"

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void * new(const void * type, ...)
{
  const size_t size = * (const size_t *) type;
  void * p = calloc(1, size);

  assert(p);

  return p;
}

void delete(void * item) {
  free(item);
}
