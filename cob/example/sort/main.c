#include "sorter.h"
#include "insertion_sorter.h"
#include "selection_sorter.h"
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
  char switcher = getchar();
  switch (switcher) {
    case 'i':
      return COB_new(InsertionSorter);
    case 's':
      return COB_new(SelectionSorter);
    default:
      return NULL;
  }
}

int main()
{
  printf("enter the first letter of your algorithm\n");
  int items[] = {5, 1, 3, 1, 2, 7};
  print_array(items, 6);
  void * sorter = create_sorter();
  if (sorter == NULL) {
    fprintf(stderr, "%s\n", "YOUR SPELLING SUCKS");
  }
  Sorter_sort(sorter, items, 6);
  printf("Size of sorter: %d\n", COB_sizeOf(sorter));
  print_array(items, 6);
}
