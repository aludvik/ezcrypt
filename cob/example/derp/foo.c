#include "foo.h"

#include <assert.h>

int Foo_foo(void * self)
{
  struct FooInterface ** foo_ptr = self;
  assert(self);
  (*foo_ptr)->foo(self);
}
