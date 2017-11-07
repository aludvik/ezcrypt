#ifndef INSERTION_SORTER_H
#define INSERTION_SORTER_H

#include <stddef.h>

extern const void * InsertionSorter;

void InsertionSorter_sort(const void * _self, int * A, size_t len);

#endif
