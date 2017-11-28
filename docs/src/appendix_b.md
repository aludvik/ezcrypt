# Appendix B - C Objects (COB)

This project uses a simplified version of the object-oriented style of C
described in "Object-Oriented Programming With ANSI-C" by Axel Schreiner. The
name of the library is C-Object or COB.

The primary motivation for creating COB was to simplify the use of polymorphism
in C with as little overhead as possible. It provides rudimentary support for
the following:

1. Interface definition and implementation
2. "Inheritance" from existing interface definitions
3. Polymorphism over implementations of a given interface
4. Constructors and destructors for objects

## Defining New Interfaces

Interfaces in COB are represented with a `struct` that contains the function
pointers for the methods defined by the interface and a base interface. For
example:

```c
struct ShapeInterface {
  struct BaseInterface parent;
  float (* area) (const void * self);
  void (* draw) (const void * self, void * pen);
};
```

The above defines a generic interface for representing shapes and declares two
methods that all shapes must implement, `area()` and `draw()`. It also uses
the `BaseInterface` interface as its parent. **All interfaces are derived from
some other interface and the derived interface must be the first member of the
struct.**

The `BaseInterface` struct comes with COB and it defines the requirements for
all classes defined within COB. Therefore, all classes must, at a minimum,
implement the `BaseInterface`. It contains three fields, `size`, `constructor`,
and `destructor`, which are used by the three main COB functions,
`COB_sizeOf()`, `COB_new()`, and `COB_delete()`, respectively.

### Inheriting from Other Interfaces

It may make sense to build on an existing interface, instead of the
`BaseInterface`. This works so long as all interfaces in the chain of
inheritance have their parent interface as the first member. For example, to
define an interface based on the `ShapeInterface` defined above, do:

```c
struct QuadrilateralInterface {
  struct ShapeInterface parent;
};
```

I am not really sure this is a useful thing to do or not though.

### Defining Selector Functions

In order to do dynamic dispatch over an interface, something has to decide which
function to call based on the specific object being used at runtime by accessing
the object's class and following the function pointer for the method being
called. This needs to be done every time a polymorphic call is made, and so it
makes sense to encapsulate the behavior in a function. Within COB these are
called "selector functions".

Selector function declarations should use the following conventions:

1. The function name should be `X_y` where `X` is the name of the interface,
   less `Interface` and `y` is the name of the function defined by the interface
   for which dynamic dispatch is desired. For example, `Shape_draw` would be the
   name of the selector function for the `draw()` method defined by the
   `ShapeInterface`.
2. The function should have the same prototype as the interface method, i.e., it
   should take the same arguments and return the same type.

The actual dynamic dispatch code for all selector functions is nearly identical,
so the macro `SELECTOR_new` has been defined to simply implementation. To use
it, pass in the interface identifier, interface method, and the method
arguments.

The following is a full example for implementing the `Shape_draw` selector
function:

```c
void Shape_draw(const void * self, void * pen) {
  SELECTOR_new(ShapeInterface, draw, self, pen)
}
```

## Implementing Interfaces

Interfaces are implemented by a creating a new "class". A class is a just a
static instance of the interface struct. This means it contains the size of the
struct implementing the interface and function pointers to all the methods
defined by the struct.

### Defining the Class

Practically speaking, implementing an interface requires defining a new struct
that contains all the data used by the new implementation, defining all the
methods required by the interface, and then "wiring everything up".

One important detail is that the struct for which the interface will be
implemented must contain a void pointer as its first member. This will be filled
in at instantiation with a pointer to the class.

As an example, consider implementing the `ShapeInterface` for a circle. First we
define the struct that contains all the data for this implementation. In this
case this is just the required void pointer and a `radius`.

```c
struct Circle {
  const void * class;
  unsigned radius;
};
```

Next we need to implement the methods required by the `ShapeInterface` and all
parent interfaces, in this case `BaseInterface`. These methods are:

```c
// Methods defined by BaseInterface
void * (* constructor) (void * self, va_list * args);
void * (* destructor) (void * self);

// Methods defined by ShapeInterface
float (* area) (const void * self);
void (* draw) (const void * self, void * pen);
```

The actual names of the functions you define to implement these methods is not
important, so long as the function signatures match. The recommended convention
is to name them `X_y` where `X` is the name of the struct containing the data
and `y` is the name of the method being implemented.

For example, the following definitions could be used for the `Circle` class:

```c
void Circle_constructor(void * self, va_list * args) {
  ...
}

void Circle_destructor(void * self) {
  ...
}

float Circle_area(const void * self) {
  ...
}

void Circle_draw(const void * self, void * pen) {
  ...
}
```

### Upcasting

You will probably have noticed by now that all of the methods take a void
pointer as their first argument. This is a convention and it enables reusing the
same function signature across multiple structs. However, the downside is that
before the data stored in the struct can be accessed, the void pointer has to be
"upcast" to a pointer to an actual struct.

The simplest form of upcasting is to just assign the void pointer to a pointer
of the desired struct and hope the function is never called with anything that
isn't the correct struct. For example:

```c
float Circle_area(const void * \_self) {
  const struct Circle * self = \_self;
}
```

Obviously this isn't very safe.

### Implementing the Constructor

## Object Instantiation

Instances of a class are created by calling the `new()` method with the name of
the class to instantiate and a list of arguments to pass to the constructor.
For example, if Circle is a class and its constructor takes a radius, then the
following would create a new Circle object with radius 5.

```c
c = COB_new(Circle, 5);
```

The return type of `new()` is `void *` so that it can be generic. This pointer
should be upcast sooner rather than later. See "upcasting" below for details.

All objects that have been created must be destroyed with `delete()` or memory
will be leaked. Just pass the object pointer to `delete()` and the destructor
will be called:

```c
COB_delete(c);
```
