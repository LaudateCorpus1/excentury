.. _excentury:

******************
What is excentury?
******************

Excentury is a collection of libraries written in several languages
to enable to the easy integration of C++ to scripting languages. By
using the excentury formats we can use or create new C++ code and
adapt it to computational languages such as Python and MATLAB.

Motivation
==========

Scripting languages give us many advantages: faster development,
extensive libraries and an overall ease of use. They are great tools
and can help individuals with no programming experience to get
started learning how to provide instructions to a machine. They allow
us to explore ideas relatively quick without spending too much time
dealing with compiler errors and many other problems that arise from
low level languages.

The main disadvantage is that their execution is slow compared to the
execution done by those compiled to machine code. Many scripting
languages offer support to adapt low level code, thus allowing you to
gain speed in your scripts. Learning how to do this is usually no
easy task since it requires the user to be familiar with the low
level language and the process to create the library is tedious.

To see how Excentury can help us write adaptable C++ code we present
present a simple programming example.

Newton's Method
===============

`Newton's method`_ is an iterative algorithm which approximates the
roots of a function :math:`f` by providing an initial guess
:math:`x_0` and computing

.. math::

    x_{n+1} = x_n - \frac{f(x_n)}{f'(x_n)}

until an accurate value is reached. To estimate the square root of a
non-negative real number :math:`a` we can apply Newton's method to
the function :math:`f(x) = x^2-a`.

.. _`Newton's method`: http://en.wikipedia.org/wiki/Newton%27s_method

The following file ``square-root.cpp`` is a program specifically
tailored to compute the square root of 5 using Newton's method.

.. code-block:: cpp
    :linenos:

    #include <cstdlib>
    #include <cstdio>
 
    int main() {
        // INPUTS
        double a = 5;
        double x0 = 1;
        int iter = 10;
 
        // ARGUMENT CHECKING
        if (a < 0) {
            printf("input `a` must be non-negative\n");
            exit(1);
        }
 
        // NEWTON'S METHOD
        double x = x0;
        for (int i=0; i < iter; ++i) {
            x = x - (x*x - a)/(2.0*x);
        }
 
        // OUTPUT
        printf("x = %f\n", x);
    }

A drawback of creating a C++ program is that passing inputs can
become a tedious task. As beginners, we usually edit the program,
compile and execute the program many times.

.. code-block:: sh

    macbook-pro:~ jmlopez$ g++ square-root.cpp -o square-root
    macbook-pro:~ jmlopez$ ./square-root
    x = 2.236068

After changing the value of ``a`` to ``2`` we obtain

.. code-block:: sh

    macbook-pro:~ jmlopez$ g++ square-root.cpp -o square-root
    macbook-pro:~ jmlopez$ ./square-root
    x = 1.414214

To avoid recompiling a program over and over again we can provide
inputs via the command line or we can make the program read from a
file. Consider the following modification in lines 6 through 8:

.. code-block:: cpp
    :linenos:
    
    #include <cstdlib>
    #include <cstdio>

    int main(int argc, char** argv) {
        // INPUTS
        double a = atof(argv[1]);
        double x0 = atof(argv[2]);
        int iter = atoi(argv[3]);

        // ARGUMENT CHECKING
        if (a < 0) {
            printf("input `a` must be non-negative\n");
            exit(1);
        }

        // NEWTON'S METHOD
        double x = x0;
        for (int i=0; i < iter; ++i) {
            x = x - (x*x - a)/(2.0*x);
        }

        // OUTPUT
        printf("x = %f\n", x);
    }

This program now accepts inputs from the command line.

.. code-block:: sh

    macbook-pro:~ jmlopez$ g++ square-root.cpp -o square-root
    macbook-pro:~ jmlopez$ ./square-root 5 1 10
    x = 2.236068
    macbook-pro:~ jmlopez$ ./square-root 2 1 10
    x = 1.414214
    macbook-pro:~ jmlopez$ ./square-root 10 1 10
    x = 3.162278

This method is perfectly fine even with programs with a large amount
of inputs. The problem is that the program needs to be written
carefully to take into account these inputs. Notice that the program
would halt execution or something would go extremely wrong if we do
not provide the correct inputs to the functions.

.. code-block:: sh

    macbook-pro:~ jmlopez$ ./square-root 10 1
    Segmentation fault: 11

As it so happens, we forget the usage of a software after a time of
inactivity. For this we have the "*man*" pages or some source of
documentation. Documentation is often one of the most neglected parts
of a software. The aim of Excentury is to keep a well documented
source code which is easy to adapt to scripting languages.

Excentury
=========

We have seen how a simple C++ program can be written and how
troublesome making a simple routine work can be. Scripting languages
function give us a safe sandbox in which we can call a function
without having the program crash. Instead they throw errors which can
then be dealt with. The idea behind excentury is to create one
document that ties documentation, along with the source code to
provide a package which can easily be exported to a scripting
language of our choice.

In the next section we discuss the installation process of Excentury
and then proceed to follow up on how to adapt our routine to C++,
MATLAB and Python.
