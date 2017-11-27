#ifndef COB_H
#define COB_H

#include <stdarg.h>
#include <stddef.h>

void * COB_new(const void * class, ...);

void COB_delete(void * object);

size_t COB_sizeOf(void * object);

/* To define a concrete class, implement each of the methods declared in the
 * abstract class and then declare a static instance of the abstract class,
 * mapping all the concrete functions to their appropriate function pointers.
 */
struct BaseInterface {
  size_t size;
  void * (* constructor) (void * self, va_list * args);
  void * (* destructor) (void * self);
};

/* Encapsulates the "wiring up" of methods to a struct in order to implement
 * a given abstract class. NAME should be an identifier for a previously
 * defined struct, IMPLEMENTS should be an identifier for a previously defined
 * abstract class, and the remaining arguments should be a list of functions
 * that implement the methods defined by the abstract class.
 */
#define CLASS_new(NAME, IMPLEMENTS, ...) \
  static const struct IMPLEMENTS _ ## NAME = { \
    sizeof(struct NAME), \
    __VA_ARGS__ \
  }; \
  const void * NAME = & _ ## NAME;

#define SELECTOR_new(INTERFACE, FUNCTION, ...) \
  struct INTERFACE * const * ptr = self; \
  assert(ptr); \
  return (*ptr)->FUNCTION(__VA_ARGS__);

#endif
