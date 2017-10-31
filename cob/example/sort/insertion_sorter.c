#include "insertion_sorter.h"
#include "sorter.h"

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>

struct InsertionSorter {
  const void * abstract_sorter;
};

void * InsertionSorter_constructor(void * self, va_list * args)
{
  return self;
}

void * InsertionSorter_destructor(void * self)
{
  return self;
}

void InsertionSorter_sort(const void * _self, int * A, size_t len)
{
  const struct InsertionSorter * self = _self;
  assert(self);

  int i = 1;
  while (i < len) {
    int j = i;
    while (j > 0 && A[j-1] > A[j]) {
      int temp = A[j];
      A[j] = A[j-1];
      A[j-1] = temp;
      j = j - 1;
    }
    i = i + 1;
  }
}

static const struct AbstractSorter _InsertionSorter = {
  sizeof(struct InsertionSorter),
  InsertionSorter_constructor,
  InsertionSorter_destructor,
  InsertionSorter_sort
};

const void * InsertionSorter = &_InsertionSorter;
