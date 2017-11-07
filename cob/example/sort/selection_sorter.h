#ifndef SELECTION_SORTER_H
#define SELECTION_SORTER_H

#include <stddef.h>

extern const void * SelectionSorter;

void SelectionSorter_sort(const void * _self, int * A, size_t len);

#endif
