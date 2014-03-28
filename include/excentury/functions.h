/** FUNCTIONS.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: July 05, 2012
% Last Modified: November 26, 2013
% NOTE: See http://stackoverflow.com/a/12607293/788553
*/

#ifdef XC_FUNCTIONS_DEBUG
#define DEBUGOFF XC_FUNCTIONS_DEBUG
#include "debugoff.h"
#endif

namespace excentury {

template<class Function, class InterfaceType, class T>
inline void communicate(Function function_, InterfaceType& interface_,
                        T& object_, const char* name_) {
    trace("Function: default communicate('%s')\n", name_);
    function_(interface_, object_, name_);
}

struct InfoImplementation {
    template<class InterfaceType, class T>
    inline void operator()(InterfaceType& interface_, T& object_,
                           const char* name_) {
        trace("Function: InfoImplementation('%s')\n", name_);
        interface_.transmit_string(name_);
        info(interface_, object_);
    }
};

template<class InterfaceType, class T>
void info(InterfaceType& interface_, T& object_, const char* name_) {
    trace("Function: info('%s') calls communicate(impl)\n", name_);
    communicate(InfoImplementation(), interface_, object_, name_);
}

template<class InterfaceType, class T>
void info(InterfaceType& interface_, T& object_) {
    trace("Function: info() calls interface_.info\n");
    interface_.info(object_);
}

struct DataImplementation {
    template<class InterfaceType, class T>
    inline void operator()(InterfaceType& interface_, T& object_,
                           const char* name_) {
        trace("Function: DataImplementation('%s')\n", name_);
        switch (type(object_)) {
            case 'C': case 'N': case 'I': case 'R':
                trace("  -->interface_.data\n");
                interface_.data(object_);
                break;
            default:
                trace("  -->data()\n");
                data(interface_, object_, name_);
        }
    }
};

template<class InterfaceType, class T>
void data(InterfaceType& interface_, T& object_, const char* name_) {
    trace("Functions: data('%s')\n", name_);
    communicate(DataImplementation(), interface_, object_, name_);
}

struct AppendSampleImplementation {
    template<class InterfaceType, class T>
    inline void operator()(InterfaceType& interface_, T& object_,
                           const char*) {
        trace("Function: AppendSampleImplementation()\n");
        interface_.store_sample(object_);
    }
};

template<class InterfaceType, class T>
void append_sample(InterfaceType& interface_, T& object_,
                   const char* name_) {
    trace("Function: append_sample('%s') calls communicate(impl)\n",
          name_);
    communicate(AppendSampleImplementation(),
                interface_, object_, name_);
}

}

#ifdef XC_FUNCTIONS_DEBUG
#include "debug.h"
#endif
