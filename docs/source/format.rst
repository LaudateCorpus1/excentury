.. _format:

****************
Excentury Format
****************

To be able to seamlessly adapt a piece of C++ code to a script
language we need a way to communicate between C++ and the scripting
language. To understand how this communication process works we must
first examine the excentury file format.

Basic Types
===========

In the C++ language there are several basic datatypes. These types
help us represent integers, real numbers and characters. To be able
to store information we need to be able to store the type of the
object we are storing along with its value. This could have been done
in several ways but for simplicity we have chosen to declare a
datatype by the type of object that is being stored along with the
number of bytes that it is required for it in memory.

There are several datatypes which represent integers, these are
``signed char``, ``short int``, ``int`` and ``long int``. To be able
to represent ``short int`` for instance we can state ``I2``, meaning
an integer of 2 bytes. The following table shows all the basic
datatypes in C++ along with its excentury representation.

=========================  ===========  ====================================
 Type name                  Excentury    Denotes
=========================  ===========  ====================================
**char**                    ``C 1``      character of 1 byte
*unsigned* **char**         ``N 1``      natural number of 1 byte: 0 to 255
*unsigned short* **int**    ``N 2``      natural number of 2 bytes
*unsigned* **int**          ``N 4``      natural number of 4 bytes
*unsigned long* **int**     ``N 8``      natural number of 8 bytes
*signed* **char**           ``I 1``      integer of 1 byte: -128 to 127
*short* **int**             ``I 2``      integer of 2 bytes
**int**                     ``I 4``      integer of 4 bytes
*long* **int**              ``I 8``      integer of 8 bytes
**float**                   ``R 4``      real number of 4 bytes
**double**                  ``R 8``      real number of 8 bytes
=========================  ===========  ====================================

These basic types are the building blocks for all possible datatypes
that we might need, these help us build structures which need to be
adapted to excentury in order to store them in a file.


XC files
========

The idea behind the excentury format is that the content of the file
must contain all the information so that we may load its data into a
scripting language. The following file for instance, does not contain
all the necessary information to load variables into a scripting
language.

.. code-block:: xc
    :linenos:
    
    -1 3.14

Here we can tell that the file contains two values, the integer -1 and
the real number 3.14. This however, does not say how it was previously
stored in C++. One way to correct this is to write the file as follows

.. code-block:: xc
    :linenos:
    
    2
    a I 4 -1
    b R 8 3.14

The file states that are two variables. The first one is an integer
of 4 bytes with value -1 and it should be assigned the name ``a``
when loaded. The second variable is a real number of 8 bytes of value
3.14 and should be named ``b``.

Structures
==========

To store structures we need to find a way of serializing its information with
the minimum amount of information. Suppose that we wish to store
two structures, a ``Point`` and a ``Line``.

.. code-block:: cpp

    class Point {
    public:
        double x, y;
        Point(): x(1), y(1){}
        Point(double a1, double b2): x(a1), y(b2){}
    };
    
    class Line {
    public:
        Point a, b;
        Line(): a(0, 0), b(1, 1) {}
        Line(int a1, double b1, int a2, double b2):
            a(a1, b1), b(a2, b2) {}
    };

For the moment, let us assume that we have taught excentury how
these two structures need to be serialized. A file containing a
``Point`` named ``point_obj`` and a ``Line`` named ``line_obj`` may
possibly look as follows

.. code-block:: xc

    2
    Point x R 8 y R 8
    Line a S Point b S Point
    2
    point_obj S Point 100.0 200.0
    line_obj S Line 1.0 2.0 3.0 4.0

This file states that there are 2 structure definitions. The first
one is for ``Point``. To read a definition we simply read pairs of
tokens: name and type. For a ``Point`` we have that its first member
is ``x`` and it is a real number of 8 bytes (``R 8``). The second
member is ``y`` and it is a real number of 8 bytes. Here we have to
rely on the new line character to know that there are no other
members for ``Point``. Similarly, for the ``Line`` definition we have
that its first member is named ``a`` and it is a ``Point`` structure
(``S Point``) while its second member is a ``Point`` structure named
``b``. This first section we just described is the dictionary for the
file. This part contains all the definitions of structures stored in
the file.

The second part contains the actual data. Here we can see that the
file contains 2 objects. The first one is called ``point_obj``. This
is a structure of type ``Point``. Since we now know the definition
for a ``Point`` we now know that we expect two values: a real number
``x`` and a real number ``y``. In this case these values are 100 and
200. The second object we have a ``Line`` structure. This one is made
up of two points. So we must first the first point ``a`` which has
members ``x`` and ``y``, thus the member ``a`` has member ``x`` of
value 1 and member ``y`` of value 2. Similarly for the member ``b`` we
have values 3 and 4.

To store a structure we first need to tell Excentury how to store it.
This however, will be covered in a later section. For now, we must
mention one last object that is essential to the excentury format.

Tensors: Multidimensional Arrays
================================

Arrays are essential to every programming language. Here we will give
a brief introduction on how we decided to store them in the excentury
format.

To store an array of integers of 4 bytes we could state the variable
name followed by ``A I 4`` followed by the number of elements in the
array and their values. For instance

.. code-block:: xc

    array_name A I 4 3 1 2 3

This was the original idea on how to store arrays. Similarly for
matrices we would use the letter ``M`` but this time we would use two
values to store its dimension.

.. code-block:: xc

    matrix_name M I 4 2 3 1 2 3 4 5 6

One problem with this notation is that we assumed that the
information was stored in column major form. That is the matrix in
the previous file is

.. math::

    \left[ \begin{array}{cc}
    1 & 4 \\
    2 & 5 \\
    3 & 6
    \end{array} \right] 

We can overcome this problem by adding a 0 if we want column major
or 1 if we want row major. The main problem when storing arrays and
matrices however is that if we continue naming these structures we
will soon find that we run out of names. For instance, an array is
simply a sequence of objects. An array of arrays is called a matrix.
An array of matrices is, well, a tensor of dimension 3. A
multidimensional array is a tensor.

To specify a tensor we can use ``T <type>`` where type is either a
basic type, a structure or a tensor. After that we must specify if it
is row major or column major followed by the number of dimensions of
the tensor and its dimensions. Finally we write the data.

To specify the previous array and matrix we would write the following
excentury file

.. code-block:: xc

    0 2
    array_name T I 4 0 1 3 1 2 3
    matrix_name T I 4 0 2 2 3 1 2 3 4 5 6

There is one type of array which is special that treating it as a
tensor may be considered a waste of resources. A sequence of
characters is usually known as a ``string``. This type of array is
special in excentury and it has been given the type ``W``. For
instance to store the string ``"hello world"`` we can use::

    0 1
    str_obj W 11 hello world

This says that ``str_obj`` is a word (``W``) of 11 characters.

Summary
=======

The excentury file format takes the following form

.. code-block:: xc

    <number of definition>
    <structure name> [<member name> <type>] ...
    ...
    <number of objects>
    <variable name> <type> <data>
    <variable name> T <type> <row major:1, column major: 0> <dimension> <dimensions> <data>
    <variable name> W <string size> <data>
    ...

To write this file format we can use C++, Python or MATLAB. See each
of their sections for more information and examples on how to do it.
