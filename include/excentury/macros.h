/** MACROS.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/

Macros
======

Color
-----

By default, if debug mode is on, it will display some messages with
color. If this is not desired then you can turn it off my defining
the macro NOCOLOR before the inclusion of this header file. The color
macros are the following:

 - `XC_BD`: Bold
 - `XC_RC`: Red Color
 - `XC_GC`: Green Color
 - `XC_YC`: Yellow Color
 - `XC_BC`: Blue Color
 - `XC_MC`: Magenta Color
 - `XC_CC`: Cyan Color
 - `XC_BRC`: Bold Red Color
 - `XC_BGC`: Bold Green Color
 - `XC_BYC`: Bold Yellow Color
 - `XC_BBC`: Bold Blue Color
 - `XC_BMC`: Bold Magenta Color
 - `XC_BCC`: Bold Cyan Color

Auxilary
--------

 - `XC_FUNC`: Shorcut for `__PRETTY_FUNCTION__` if compiling with
              GNU Compiler.
 - `XC_PRINT_CLASS_NAME(obj)`: This macro is used to print the class
                               name of the given object to stderr.
 - `XC_PRINT_FUNCTION_NAME`: This macro is used to print the name of
                             the function in current use.

Core
----

 - To be completed ...

*/

#ifndef XC_MACROS
#define XC_MACROS

#ifdef NOCOLOR
    #define XC_BD(txt) #txt
    #define XC_RC(txt) #txt
    #define XC_GC(txt) #txt
    #define XC_YC(txt) #txt
    #define XC_BC(txt) #txt
    #define XC_MC(txt) #txt
    #define XC_CC(txt) #txt
    #define XC_BRC(txt) #txt
    #define XC_BGC(txt) #txt
    #define XC_BYC(txt) #txt
    #define XC_BBC(txt) #txt
    #define XC_BMC(txt) #txt
    #define XC_BCC(txt) #txt
    #define XC_BD_BEGIN ""
    #define XC_BD_END ""
#else
    #define XC_BD(txt) "\033[1m" #txt "\033[0m"
    #define XC_RC(txt) "\033[31m" #txt "\033[0m"
    #define XC_GC(txt) "\033[32m" #txt "\033[0m"
    #define XC_YC(txt) "\033[33m" #txt "\033[0m"
    #define XC_BC(txt) "\033[34m" #txt "\033[0m"
    #define XC_MC(txt) "\033[35m" #txt "\033[0m"
    #define XC_CC(txt) "\033[36m" #txt "\033[0m"
    #define XC_BRC(txt) "\033[1;31m" #txt "\033[0m"
    #define XC_BGC(txt) "\033[1;32m" #txt "\033[0m"
    #define XC_BYC(txt) "\033[1;33m" #txt "\033[0m"
    #define XC_BBC(txt) "\033[1;34m" #txt "\033[0m"
    #define XC_BMC(txt) "\033[1;35m" #txt "\033[0m"
    #define XC_BCC(txt) "\033[1;36m" #txt "\033[0m"
    #define XC_BD_BEGIN "\033[1m"
    #define XC_BD_END "\033[0m"
#endif
#include <iomanip>
#ifdef __GNUG__
    #include <cxxabi.h>
    #define XC_FUNC __PRETTY_FUNCTION__
    #define XC_PRINT_FUNCTION_NAME fprintf(stderr, \
            " executing: \n\n    " XC_BD(%s\n\n), XC_FUNC);
#else
    #define XC_FUNC ""
    #define XC_PRINT_FUNCTION_NAME ((void)0)
#endif
namespace excentury {
    void print_class_name(const std::type_info& info) {
    #ifdef __GNUG__
        char* realname;
        int status;
        realname = abi::__cxa_demangle(info.name(), 0, 0, &status);
        fprintf(stderr, "%s", realname);
        free(realname);
    #else
        fprintf(stderr, "%s", info.name().c_str());
    #endif
    }
}
#define XC_PRINT_CLASS_NAME(class) print_class_name(typeid(class))

//--------------------------------------------------------------------
// CORE MACROS
//--------------------------------------------------------------------
#define XC_DUMP_DATATYPE(object,var) \
    template<> inline const char* type_name(const object&) { \
        return #object; \
    } \
    template<class Function, template<mode m> class InterfaceType> \
    inline void communicate(Function f, \
                            InterfaceType<dump_mode>& interface, \
                            object& var, const char*)

#define XC_LOAD_DATATYPE(object,var) \
    template<class Function, template<mode m> class InterfaceType> \
    inline void communicate(Function f, \
                            InterfaceType<load_mode>& interface, \
                            object& var, const char*)

#define XC_DUMP(var,varname) f(interface, var, varname)
#define XC_LOAD(var) f(interface, var, "")

#define XC_DUMP_TENSOR(object,var,sample) \
    template<> inline char type(const object&) {return 'T';} \
    template<class InterfaceType> \
    void info(InterfaceType& interface, object& var) { \
        interface.transmit_type('T'); \
        info(interface, sample); \
    } \
    template<class Function, template<mode m> class InterfaceType> \
    inline void communicate(Function f, \
                            InterfaceType<dump_mode>& interface, \
                            object& var, const char*)

#define XC_LOAD_TENSOR(object,var) \
    template<class Function, template<mode m> class InterfaceType> \
    inline void communicate(Function f, \
                            InterfaceType<load_mode>& interface, \
                            object& var, const char*)

#define XC_DUMP_TEMPLATED_TENSOR(temp_arg,object,var,sample) \
    template<temp_arg> struct TypeAux< object > { \
        static inline char type() {return 'T';} \
    }; \
    template<temp_arg, class InterfaceType> \
    void info(InterfaceType& interface, object& var) { \
        interface.transmit_type('T'); \
        info(interface, sample); \
    } \
    template<temp_arg, class Function, \
             template<mode m> class InterfaceType> \
    inline void communicate(Function, \
                            InterfaceType<dump_mode>& interface, \
                            object& var, const char*)

#define XC_LOAD_TEMPLATED_TENSOR(temp_arg,object,var) \
    template<temp_arg, class Function, \
             template<mode m> class InterfaceType> \
    inline void communicate(Function f, \
                            InterfaceType<load_mode>& interface, \
                            object& var, const char* varname)

#define XC_BYTE(rm) interface.transmit_byte(rm)
#define XC_SIZE(var) interface.transmit_number(var)
#define XC_ARRAY(ptr,size) interface.data(ptr, size)

#define XC_DUMP_WORDS(object,var) \
    template<> inline char type(const object&) {return 'W';} \
    template<class InterfaceType> \
    void info(InterfaceType& interface, object&) { \
        interface.transmit_type('W'); \
    } \
    template<class Function, \
             template<mode m> class InterfaceType> \
    inline void communicate(Function, \
                            InterfaceType<dump_mode>& interface, \
                            object& var, const char*)


#define XC_LOAD_WORDS(object,var) \
    template<class Function, \
             template<mode m> class InterfaceType> \
    inline void communicate(Function, \
                            InterfaceType<load_mode>& interface, \
                            object& var, const char*)

#endif
