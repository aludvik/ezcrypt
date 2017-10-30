#include "derp.h"
#include "herp.h"
#include "foo.h"
#include "../../src/cob.h"

#include <stdio.h>

int main() {
  void * derp = new(Derp);
  void * herp = new(Herp);
  printf("%d\n", Foo_foo(derp));
  printf("%d\n", Foo_foo(herp));
  delete(derp);
  delete( herp);
  return 0;
}
