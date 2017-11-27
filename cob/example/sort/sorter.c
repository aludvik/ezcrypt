#include "sorter.h"

#include <assert.h>

void Sorter_sort(const void * self, int * items, size_t len)
{
  SELECTOR_new(SorterInterface, sort, self, items, len)
}
