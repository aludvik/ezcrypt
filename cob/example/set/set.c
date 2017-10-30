#include "set.h"
#include "element.h"

#include <stddef.h>
#include <assert.h>

struct Set {
  unsigned count;
};

struct Element {
  unsigned count;
  void * in;
};

void * Set_add(void * _set, void * _element)
{
  struct Set * set = _set;
  struct Element * element = _element;

  assert(set);
  assert(element);

  if (! element->in) {
    element->in = set;
  } else {
    assert(element->in == set);
  }
  element->count++;
  set->count++;
  return element;
}

void * Set_find(void * _set, void * _element)
{
  struct Element * element = _element;
  assert(_set);
  assert(element);
  return element->in == _set ? (void *) element : 0;
}

int Set_contains(void * _set, void * _element)
{
  return Set_find(_set, _element) != 0;
}

void * Set_drop(void * _set, void * _element)
{
  struct Set * set = _set;
  struct Element * element = Set_find(set, _element);
  if (element) {
    if (-- element -> count == 0) {
      element -> in = 0;
    }
    -- set -> count;
  }
  return element;
}

unsigned Set_count(void * _set)
{
  struct Set * set = _set;
  assert(set);
  return set -> count;
}

int Element_differ(const void * a, const void * b) {
  return a != b;
}

static const size_t _Set = sizeof(struct Set);
const void * Set = & _Set;

static const size_t _Element = sizeof(struct Element);
const void * Element = & _Element;
