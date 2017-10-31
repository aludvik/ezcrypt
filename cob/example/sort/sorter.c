#include "sorter.h"

#include <assert.h>

void Sorter_sort(const void * self, int * items, size_t len)
{
  struct AbstractSorter * const * sorter_ptr = self;
  assert(sorter_ptr);
  (*sorter_ptr)->sort(self, items, len);
}
