#include <stdio.h>

#include "herp.h"
#include "foo.h"
#include "../../src/cob.h"

#include <assert.h>

struct Herp {
  const void * class;
  int herp;
};

void * Herp_constructor(void * _self, va_list * args)
{
  struct Herp * self = _self;
  self->herp = 2;
  return self;
}

void * Herp_destructor(void * self)
{
  return self;
}

int Herp_foo(void * _self) {
  struct Herp * self = _self;
  assert(self);
  return self->herp;
}

static const struct AbstractFoo _Herp = {
  sizeof(struct Herp),
  Herp_constructor,
  Herp_destructor,
  Herp_foo
};

const void * Herp = & _Herp;
