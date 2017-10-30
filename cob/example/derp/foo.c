#include "foo.h"

#include <assert.h>

int Foo_foo(void * self)
{
  struct AbstractFoo ** foo_ptr = self;
  assert(self);
  (*foo_ptr)->foo(self);
}
