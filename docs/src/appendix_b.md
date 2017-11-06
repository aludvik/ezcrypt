# Appendix B - C Objects (COB)

This project uses a simplified version of the object-oriented style of C
described in "Object-Oriented Programming With ANSI-C" by Axel Schreiner.

## Defining new Interfaces

### Inheriting Existing Interfaces

### Defining Selector Functions

## Implementing Interfaces

## Object Instantiation

Instances of a class are created by calling the `new()` method with the name of
the class to instantiate and a list of arguments to pass to the constructor.
For example, if Circle is a class and its constructor takes a radius, then the
following would create a new Circle object with radius 5.

    c = new(Circle, 5);

The return type of `new()` is `void *` so that it can be generic. This pointer
should be upcast sooner rather than later. See "upcasting" below for details.

All objects that have been created must be destroyed with `delete()` or memory
will be leaked. Just pass the object pointer to `delete()` and the destructor
will be called:

    delete(c);

## Upcasting
