.. _install:

********************
Installing Excentury
********************

There is more than one way to install Excentury.

The Easy Way
============

The easiest way to install Excentury is to use ``pip``. If you wish
to perform a global installation and you have admin rights then do

.. code-block:: sh

    sudo pip install excentury

or to install in some directory under your user account

.. code-block:: sh

    pip install --user excentury


Installing on \*nix Systems
===========================

From the command line do the following (where x.y is the version
number):

.. code-block:: sh

    wget https://pypi.python.org/packages/source/e/excentury/excentury-x.y.tar.gz
    tar xvzf excentury-x.y.tar.gz
    cd excentury-x.y/
    sudo python3 setup.py install

The last command can be replaced by ``python3 setup.py install
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

    python3 -m excentury install

This will print several messages describing some paths. To verify
that ``excentury`` is now in your path you can try the help option

.. code-block:: sh

    excentury -h

The ``install`` command also takes care of the C and C++ include
paths. This will make sure that you can access the C++ libraries as
well as the MATLAB libraries.
