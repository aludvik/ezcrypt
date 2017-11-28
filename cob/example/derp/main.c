#include "derp.h"
#include "herp.h"
#include "foo.h"
#include "../../src/cob.h"

#include <stdio.h>

int main() {
  void * derp = COB_new(Derp);
  void * herp = COB_new(Herp);
  printf("%d\n", Foo_foo(derp));
  printf("%d\n", Foo_foo(herp));
  COB_delete(derp);
  COB_delete( herp);
  return 0;
}
