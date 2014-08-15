/** EXCENTURY.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: BSD License
% Jul 05, 2012 -- Aug 15, 2014

This file provides access to all the functions and classes defined in
excentury. All macros defined by excentury start with XC (excentury)
followed by an underscore and a name in capital letters.

*/

#ifndef EXCENTURY_H
#define EXCENTURY_H

// Includes mex.h
#include "hook/matlab.h"

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <typeinfo>
#include <exception>
#include <sys/time.h>

#include "macros.h"
#include "debug.h"
#include "error.h"
#include "types.h"

#include "communicator.h"
#include "functions.h"
#include "datatype.h"

#include "interface/textInterface.h"
#include "interface/stextInterface.h"
// #include "interface/MLInterface.h"

#include "objects.h"

#include "tensor/tensor.h"
#include "tensor/staticTensor.h"
#include "tensor/dynamicTensor.h"

#include "tools/reporter.h"
#include "tools/rand.h"

#include "hook/cpp.h"

#endif
