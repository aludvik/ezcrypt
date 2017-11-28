#ifndef COB_H
#define COB_H

#include <stdarg.h>
#include <stddef.h>

/// Instantiate a new instance of the given class. Returns a pointer to the
/// instantiated object of the given class. Arguments after the class name are
/// passed to the classes constructor.
void * COB_new(const void * class, ...);

/// Call the destructor function for this object, which should release any
/// resources held by the object.
void COB_delete(void * object);

/// Return the size of the given object in memory, as indicated by the `size`
/// field of the object's class.
size_t COB_sizeOf(void * object);

/// To define a concrete class, implement each of the methods declared in the
/// abstract class and then declare a static instance of the abstract class,
/// mapping all the concrete functions to their appropriate function pointers.
struct BaseInterface {
  size_t size;
  void * (* constructor) (void * self, va_list * args);
  void * (* destructor) (void * self);
};

/// Encapsulates the "wiring up" of methods to a struct in order to implement a
/// given interface. NAME should be an identifier for a previously defined
/// struct, IMPLEMENTS should be an identifier for a previously defined
/// interface, and the remaining arguments should be a list of functions that
/// implement the methods defined by the interface.
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
