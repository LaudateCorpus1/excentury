"""excentury setup script"""

import imp
import os.path as pt
from setuptools import setup


def get_version():
    "Get version & version_info without importing excentury.__init__ "
    path = pt.join(pt.dirname(__file__), 'excentury', '__version__.py')
    mod = imp.load_source('excentury_version', path)
    return mod.VERSION, mod.VERSION_INFO

VERSION, VERSION_INFO = get_version()

DESCRIPTION = "Call C++ from Python and MATLAB"
LONG_DESCRIPTION = """
Excentury is a set of libraries written in C++ that enables easy
integration of C++ code into Python and MATLAB projects.
"""

DEV_STATUS_MAP = {
    'alpha': '3 - Alpha',
    'beta': '4 - Beta',
    'rc': '4 - Beta',
    'final': '5 - Production/Stable'
}
if VERSION_INFO[3] == 'alpha' and VERSION_INFO[4] == 0:
    DEVSTATUS = '2 - Pre-Alpha'
else:
    DEVSTATUS = DEV_STATUS_MAP[VERSION_INFO[3]]


setup(name='excentury',
      version=VERSION,
      description=DESCRIPTION,
      long_description=LONG_DESCRIPTION,
      keywords='c++ python matlab interoperability',
      author='Manuel Lopez',
      author_email='jmlopez.rod@gmail.com',
      url='http://excentury.readthedocs.org',
      license='BSD License',
      packages=[
          'excentury',
          'excentury.command',
          'excentury.lang',
          ],
      platforms=['Darwin', 'Linux'],
      scripts=['bin/excentury'],
      install_requires=[
          'numpy>=1.8.2',
          'six>=1.7.3',
          ],
      package_data={'': ['*.h', '*.m']},
      include_package_data=True,
      classifiers=[
          'Development Status :: %s' % DEVSTATUS,
          'License :: OSI Approved :: BSD License',
          'Operating System :: MacOS :: MacOS X',
          'Operating System :: POSIX :: Linux',
          'Programming Language :: Python :: 2',
          'Topic :: Scientific/Engineering :: Mathematics',
          ],
     )
