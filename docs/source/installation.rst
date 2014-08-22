.. _install:

********************
Installing Excentury
********************

Before we can get started adapting our C++ code to our favorite
scripting language we must have a C++ compiler installed and a copy
of Excentury. First we start with the installation of Excentury.

Pip or Manual Installation
==========================

The easiest way to install Excentury is to use ``pip``. If you wish
to perform a global installation and you have admin rights then do

.. code-block:: sh

    sudo pip install excentury

or to install in some directory under your user account

.. code-block:: sh

    pip install --user excentury

Or if you prefer to do do a manual installation then you may do the
following from the command line (where x.y is the version number):

.. code-block:: sh

    wget https://pypi.python.org/packages/source/e/excentury/excentury-x.y.tar.gz
    tar xvzf excentury-x.y.tar.gz
    cd excentury-x.y/
    sudo python setup.py install

The last command can be replaced by ``python setup.py install
--user``. See `PyPI <https://pypi.python.org/pypi/excentury/>`_ for
all available versions.

Excentury executable
====================

To be able to call ``excentury`` from the command line you must have
the executable directory in your ``$PATH``. This can be taken care of
my calling the ``install`` command in ``excentury``. Since the
executable is not yet available you will have to call the excentury
script from python.

.. code-block:: sh

    python -m excentury install

To verify that ``excentury`` is now in your path you can try the help
option

.. code-block:: sh

    excentury -h

The ``install`` command also takes care of the C and C++ include
paths. This will make sure that you can access the C++ libraries as
well as the MATLAB libraries.

OS X
====

To be able to use excentury we need a C++ compiler. We may obtain
this by installing `XCode <https://developer.apple.com/xcode/>`_.

The next step is not required but if you are having trouble
installing python packages then you may want to try `Homebrew
<http://brew.sh/>`_. Try installing it and then try installing a
fresh installation of python.

MATLAB
======

Regardless of what operating system we are using, we need to make
sure that our ``$PATH`` contains the ``mex`` script that comes with
MATLAB.

Before we can use excentury we need to make sure that ``mex`` is
working properly. To do a test, you should try to work with one of
the mex `examples
<http://www.mathworks.com/help/matlab/matlab_external/build-an-executa
ble-mex-file.html>`_ provided by MathWorks.

.. note::

    With every release of OS X and MATLAB there are a few changes
    that need to be done. If either the operating system or MATLAB is
    updated you should always first try to compile one of their
    examples to make sure that mex files can be compiled successfully
    before attempting to figure out what is wrong with excentury.

.. warning::

    If you have OS X 10.9 and you are having trouble compiling the
    mex example then you may want to look at this stackoverflow
    `question <http://stackoverflow.com/q/22367516/788553>`_. Note
    that one solution is to upgrade your ``gcc/g++`` compilers using
    either homebrew or macports and specify this in the mex setup.
