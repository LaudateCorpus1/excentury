/** DEBUG.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: July 05, 2012
% Last Modified: November 26, 2013

Debugging
=========

This header file was created for a single reason: Spending too much
time debugging. In past experiences I have been able to find many
bugs by writing messages that allow me to see how the program is
working. Once I have found the error I then have to remove these
messages so that the program can work smoothly once again.

I have designed excentury with the sole purpose of making an
efficient standalone program. For this reason I have three main
functions in this header file: `exitif`, `debug` and `trace`.

These functions are macros which will expand to a command if the
DEBUG macro is defined before the inclusion of this file. Otherwise
those functions will expand to nothing. If the DEBUG macro is defined
it is expected to be either the integers 1, 2, or 3. These are the
levels of debugging using excentury.

Debuging Level 1
----------------

This is the most basic level and it will allow you to use the
function `exitif`.

    exitif(condition, function_call, ...)

This is a macro which roughly expands to the following:

    if (condition) {
        printf(...)
        function_call;
        exit(1);
    }

Debuging Level 2
----------------

This level provides the function `debug`. These messages should only
be used while debuging. If the messages could help in the future then
we should replace `debug` with the level 3 function `trace`.

    debug(...)

This debug function behaves as printf but will only be expanded in
level 2 and 3.

Debuging Level 3
----------------

Provides the function `trace`. Messages will only be seen in level 3.
These are more permanent messages and should be designed to help the
debugger have a better idea of what is going on with the program.

    trace(...)

*/

#undef exitif
#undef debug
#undef trace
#ifdef DEBUG
    #define exitif(e, call_func, ...) if(e) { \
        fprintf(stderr, XC_BRC(ERROR CAUGHT BY) " " \
                XC_CC(%s) " line " XC_BD(%u), \
                __FILE__, __LINE__); \
        XC_PRINT_FUNCTION_NAME; \
        fprintf(stderr, "The error occurred because:  " \
                XC_BD(%s) "\n\n" XC_BD_BEGIN, #e); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, XC_BD_END); \
        call_func; \
        exit(1); \
    } 
    #if DEBUG > 1
        #define debug(...) fprintf(stderr, __VA_ARGS__)
        #if DEBUG > 2
            #define trace(...) fprintf(stderr, __VA_ARGS__)
        #else
            #define trace(...) ((void)0)
        #endif
    #else
        #define debug(...) ((void)0)
        #define trace(...) ((void)0)
    #endif
#else
    #define exitif(e, ...) ((void)0)
    #define debug(...) ((void)0)
    #define trace(...) ((void)0)
#endif
