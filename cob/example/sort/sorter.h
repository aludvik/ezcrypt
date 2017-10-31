#ifndef SORTER_H
#define SORTER_H

#include "../../src/cob.h"
#include <stddef.h>

struct AbstractSorter {
  // Inherit AbstractClass
  struct AbstractClass parent;
  void (* sort) (const void * self, int * items, size_t len);
};

void Sorter_sort(const void * self, int * items, size_t len);

#endif
