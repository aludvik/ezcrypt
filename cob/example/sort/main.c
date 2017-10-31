#include "sorter.h"
#include "insertion_sorter.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h>

void print_array(int * items, size_t len) {
  printf("[");
  for (int i = 0; i < len - 1; i++) {
    printf("%d, ", items[i]);
  }
  printf("%d]\n", items[len-1]);
}

void * create_sorter() {
  return new(InsertionSorter);
}

int main()
{
  int items[] = {5, 1, 3, 1, 2, 7};
  print_array(items, 6);
  void * sorter = create_sorter();
  Sorter_sort(sorter, items, 6);
  printf("Size of sorter: %d\n", sizeOf(sorter));
  print_array(items, 6);
}
