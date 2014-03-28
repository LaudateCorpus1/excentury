/** DEBUGOFF.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: November 15, 2013
% Last Modified: November 26, 2013

This file turns off the debugging macros. To use it you must use the
following two sets of code in a file:

    #ifdef FILENAME_DEBUG
    #define DEBUGOFF FILENAME_DEBUG
    #include <excentury/debugoff.h>
    #endif

    ... code ...

    #ifdef FILENAME_DEBUG
    #include <excentury/debug.h>
    #endif

If you later wish to turn off some levels of debuging in a file
you can simply define `FILENAME_DEBUG` to the levels that you
want turned off.

Level 3: Removes the use of the trace function
Level 2: Uses level 3 and removes the use of the debug function
Level 1: Removes the use of the exitif function
*/

#if DEBUGOFF < 4
    #undef trace
    #define trace(...) ((void)0)
    #if DEBUGOFF < 3
        #undef debug
        #define debug(...) ((void)0)
        #if DEBUGOFF < 2
            #undef exitif
            #define exitif(e, ...) ((void)0)
        #endif
    #endif
#endif

#undef DEBUGOFF
