#include "insertion_sorter.h"
#include "sorter.h"

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>

struct SelectionSorter {
  const void * abstract_sorter;
};

void * SelectionSorter_constructor(void * self, va_list * args)
{
  return self;
}

void * SelectionSorter_destructor(void * self)
{
  return self;
}

int find_min(int * A, size_t len)
{
  int loc = 0;
  int min = A[0];
  int i = 1;
  while (i < len) {
    if (A[i] < min) {
      loc = i;
      min = A[i];
    }
    i = i + 1;
  }
  return loc;
}

void SelectionSorter_sort(const void * _self, int * A, size_t len)
{
  const struct SelectionSorter * self = _self;
  assert(self);

  int i = 0;
  while (i < len) {
    int loc = find_min(A + i, len - i) + i;
    int temp = A[i];
    A[i] = A[loc];
    A[loc] = temp;
    i = i + 1;
  }
}

CLASS_new(
  SelectionSorter,
  AbstractSorter,
  SelectionSorter_constructor,
  SelectionSorter_destructor,
  SelectionSorter_sort
)
