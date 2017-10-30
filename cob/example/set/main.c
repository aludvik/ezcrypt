#include "set.h"
#include "element.h"
#include "../../src/mem.h"

#include <stdio.h>

int main() {
  void * s = new(Set);
  void * a = Set_add(s, new(Element));
  void * b = Set_add(s, new(Element));
  void * c = new(Element);

  if (Set_contains(s, a) && Set_contains(s, b)) {
    printf("ok\n");
  }

  if (Set_contains(s, c)) {
    printf("contains?\n");
  }

  if (Element_differ(a, Set_add(s, a))) {
    printf("differ?\n");
  }

  if (Set_contains(s, Set_drop(s, a))) {
    printf("drop?\n");
  }

  delete(Set_drop(s, a));
  delete(Set_drop(s, b));
  delete(s);

  return 0;
}
