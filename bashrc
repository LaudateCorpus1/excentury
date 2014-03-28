# Excentury local installation
#
# This bash file is meant to be used for local installation. It
# defines enviromental variables that are necessary for all the
# languages that excentury interacts with. Read the README file
# to see how to use this file properly.
#

# The path to this local installation
export XCROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Access to xcpp
export PATH=$XCROOT/bin:$PATH

# Python, MATLAB and C/C++
export PYTHONPATH=$XCROOT/python:$PYTHONPATH
export MATLABPATH=$XCROOT/matlab:$MATLABPATH
export C_INCLUDE_PATH=$XCROOT/include:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=$XCROOT/include:$CPLUS_INCLUDE_PATH

# Mathematica:
# You may have to change the paths depending on your OS to find
# MathLink.
export MMA_PATH=$GR/mathematica
unamestr=`uname`
if [[ "$unamestr" == 'Darwin' ]]; then
   MLINK="/Applications/Mathematica.app/SystemFiles/Links/MathLink"
   MLINK=$MLINK"/DeveloperKit/MacOSX-x86-64/CompilerAdditions"
elif [[ "$unamestr" == 'Linux' ]]; then
   MLINK="/usr/lib64/mathematica-9.0.1/SystemFiles/Links/MathLink"
   MLINK=$MLINK"/DeveloperKit/Linux-x86-64/CompilerAdditions"
fi
export MLINK

# PYTHON NOTE
# You need provide the directory where you are compiling the python
# shared libraries. Before using python make sure that the path is
# in the following enviroment variable
#export LD_LIBRARY_PATH=/path/to/shared/libraries:$LD_LIBRARY_PATH

# XCC_CONFIG:
# If you have a configuration file for excentury that you wish to
# use then define this variable
#export XCPP_CONFIG_PATH=/path/to/xcpp.config
