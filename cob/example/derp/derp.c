#include <stdio.h>

#include "derp.h"
#include "foo.h"
#include "../../src/cob.h"

#include <assert.h>

struct Derp {
  const void * class;
  int derp;
};

void * Derp_constructor(void * _self, va_list * args)
{
  struct Derp * self = _self;
  self->derp = 1;
  return self;
}

void * Derp_destructor(void * self)
{
  return self;
}

int Derp_foo(void * _self) {
  struct Derp * self = _self;
  assert(self);
  return self->derp;
}

CLASS_new(
  Derp,
  FooInterface,
  Derp_constructor,
  Derp_destructor,
  Derp_foo
)
