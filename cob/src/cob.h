#ifndef COB_H
#define COB_H

#include <stdarg.h>
#include <stddef.h>

// Instantiate a new instance of the given class
void * new(const void * class, ...);

// Release the resources for the given object
void delete(void * object);

void clone(void*object);

/* To define a concrete class, implement each of the methods declared in the
 * abstract class and then declare a static instance of the abstract class,
 * mapping all the concrete functions to their appropriate function pointers.
 */
struct AbstractClass {
  size_t size;
  void * (* constructor) (void * self, va_list * args);
  void * (* destructor) (void * self);
};

#endif
