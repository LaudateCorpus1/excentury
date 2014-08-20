.. _changelog:

0.2.2 (2014-08-20)
++++++++++++++++++

- Installation fixed for linux systems. All operating systems besides
  OS X are assumed to use ``.bashrc``.


0.2.1 (2014-08-19)
++++++++++++++++++

- Configuration files have access to ``ARG`` and ``CFG`` variables.
- Installation requires ``six>=1.7.3``.
- Matlab cpp writer error fixed.


0.2.0 (2014-08-18)
++++++++++++++++++

- Added in the `Python Package Index
  <https://pypi.python.org/pypi/excentury/>`_.
- Install command sets environmental variables.
- Issue with ``istringstream`` fixed for OS X 10.9.
- Default paths set to be in ``site.getuserbase()+'/lib/excentury'``.
- Python runtime errors fixed.
- Dependence on ``configparser`` has been removed.
- Empty configuration variables no longer give errors.
- Interpolation in configuration files is now available.
- Removed ``config`` command to set variables. It must be done
  manually.
- Conditional configuration allows us to use Python code in
  configuration files.
- Excentury files must include ``<excentury/excentury.h>``.
- Unit testing is done with ``bash``.
- Fixed ``IOError`` when attempting to read nonexistent config file.
- Armadillo incorporation example added.
- Excentury can create and track projects.
- A warning is issued when an excentury project is selected.


0.1.0 (2014-03-28)
++++++++++++++++++

- Initial release.
- Not registered in the Python Index.
- Must source the bashrc file for temporary installation.
- Works primarily in OS X 10.8.
