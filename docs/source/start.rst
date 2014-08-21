.. _start:

***************
Getting Started
***************

Excentury aims to provide simple and intuitive tools which we can use
to develop packages with easy. This is done via a file format where
we can write C++ code and give accessibility from MATLAB and Python
at the same time.

The format goes roughly as follows:

.. code-block:: cpp

    """Package Name
 
    Package documentation.
    """
    /* Package preamble contents */
    ----------------------------------------------------------------------
    /* Function preamble contents */
    @def{function name}
        """Function explanation. """
        @param{type1, var1, "var1 explanation"}
        @param{type2, var2, "var2 explanation"}
        @param{type3, var3, "var3 explanation"}
    @body[[
        /* Function body */
    ]]
    @ret[[
        @ret{ans1, "ans1"}
        @ret{ans2, "ans2"}
    ]]
    /* Function epilog contents */
    ----------------------------------------------------------------------
    /* Package epilog (if no more functions are defined) */

Consider the excentury file ``sample.xcpp``.

.. code-block:: cpp

    """Sample

    This package provides the functions to compute the square root of a
    non-negative real number.
 
    """
    #include <excentury/excentury.h>
 
    ----------------------------------------------------------------------
    @def{square_root}
        """Compute the square root of a number using Newton's method."""
        @param{double, a(2), "the input to the square root function"}
        @param{double, x0(1), "initial guess"}
        @param{int, iter(10), "number of iterations"}
    @body[[
        if (a < 0) {
            excentury::error("input `a` must be non-negative");
        }
        double x = x0;
        for (int i=0; i < iter; ++i) {
            x = x - (x*x - a)/(2.0*x);
        }
    ]]
    @ret[[
        @ret{x, "x"}
    ]]
    ----------------------------------------------------------------------
    @def{cpp_sqrt}
        """Call the sqrt function provided by c++"""
        @param{double, a(2), "the input sqrt"}
    @body[[
        double x = sqrt(a);
    ]]
    @ret[[
        @ret{x, "x"}
    ]]
    ----------------------------------------------------------------------
    

A key difference as opposed to a regular C++ file is how we are now
defining the section for the inputs and the outputs while leaving the
body of the function almost intact (except for line 17 where we check
for errors).

CPP
===

To try to run this example in cpp we can try the following::

    excentury sample.xcpp to cpp

This will create two valid cpp files which will then be compiled into
binaries which we can call.::

    $ sample-square_root.run -h
    usage: sample-square_root.run [-h] [-i] XC_CONTENT

    program: sample-square_root

    description:
        Compute the square root of a number using Newton's method.

    parameters:
        `a`: the input to the square root function
        `x0`: initial guess
        `iter`: number of iterations

    examples:

        generate an input file: sample-square_root.run -i > input_file.xc
        use the file: sample-square_root.run "`< input_file.xc`"

The help menu is important because it tells us how we can provide the
inputs to the program. In this case we can generate an input file::

    $ sample-square_root.run -i > input_file.xc

Since the xcpp file declared default values we can leave the file as
is and run it as follows::

    $ sample-square_root.run "`< input_file.xc`"
    0 1
    x R 8 1.414214

From here on we can simply modify the contents declared in
"input_file.xc" to change the parameters to the function. At this
moment we do not expect you to know what the xc file extension is
formatted. In future sections we will go into detail on this topic
since most of the development of C++ code should be done in a simple
C++ file instead of MATLAB or Python. Only once the C++ code runs as
expected then we can move on to using it in the interpreters.

Python
======

To be able to use our functions in the sample package we can tell
excentury to give us a python package::

    $ excentury sample.xcpp to python

Once excentury is done creating the necessary files we can work
within python::

    >>> import sample
    >>> sample.square_root(2, 1, 10)
    1.41421
    >>> sample.square_root(5, 1, 10)
    2.23607
    >>> sample.square_root(-1, 1, 10)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "/Users/jmlopez/Library/Python/2.7/lib/excentury/python/sample.py", line 45, in square_root
        raise RuntimeError(xc_error_msg)
    RuntimeError: input `a` must be non-negative

If you use the ``help`` function on the ``sample`` module you can see
that there exists two functions: the one called above and
``cpp_sqrt``.

    >>> sample.cpp_sqrt(2)
    1.41421
    >>> sample.cpp_sqrt(5)
    2.23607
    >>> sample.cpp_sqrt(-1)
    nan

MATLAB
======

Two obtain our mex function we can execute the following:

    $ excentury sample.xcpp to matlab

Then in the MATLAB prompt we can do

.. code-block:: matlab

    >> help sample.square_root
      sample.SQUARE_ROOT generated on Wed Aug 20, 2014 09:11:18 PM by xcpp
  
          Compute the square root of a number using Newton's method.
  
          parameters:
  
            `a`: the input to the square root function
            `x0`: initial guess
            `iter`: number of iterations
      

    >> sample.square_root(2, 1, 10)

    ans =

        1.4142

    >> sample.square_root(5, 1, 10)

    ans =

        2.2361

    >> sample.square_root(-1, 1, 10)
    Error using square_root_mex
    input `a` must be non-negative

    Error in sample.square_root (line 18)
        [~, out_str] = sample.square_root_mex(len_in, in_str);
 
Similarly, we can use the C++ function square root

.. code-block:: matlab

    >> help sample.cpp_sqrt
      sample.CPP_SQRT generated on Wed Aug 20, 2014 09:11:20 PM by xcpp
  
          Call the sqrt function provided by c++
  
          parameters:
  
            `a`: the input sqrt
      

    >> sample.cpp_sqrt(2)

    ans =

        1.4142

    >> sample.cpp_sqrt(5)

    ans =

        2.2361

    >> sample.cpp_sqrt(-1)

    ans =

       NaN


What's Next?
============

You may use this example to try to experiment creating function which
can be called from CPP, MATLAB or Python. The Excentury documentation
is still far from complete, for the moment you can look over the
source code to see if there are any functions that may be of interest
and give them a try.
