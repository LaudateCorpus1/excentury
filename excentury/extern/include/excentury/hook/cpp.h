/** HOOK/CPP.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: BSD License
% 2012 -- Aug 13, 2014
*/

#ifdef XC_CPP

namespace excentury {

void check_inputs(int num) {
    if (num != 2) {
        fprintf(stderr, "ERROR: Use -h for info on usage.\n");
        exit(2);
    }
}


void print_inputs(char** opt, void (*func)()) {
    if (opt[1][0] == '-' && opt[1][1] == 'i') {
        (*func)();
        exit(0);
    }
}


void print_help(char** opt, void (*func)()) {
    if (opt[1][0] == '-' && opt[1][1] == 'h') {
        fprintf(stderr,
            "usage: %s [-h] [-i] XC_CONTENT\n\n"
            , opt[0]);
        (*func)();
        fprintf(stderr,
            "examples:\n\n"
            "    generate an input file: %s -i > input_file.xc\n"
            "    use the file: %s \"`< input_file.xc`\"\n\n"
            "built on %s - %s\n"
            , opt[0], opt[0], __DATE__, __TIME__);
        exit(0);
    }
}

}

#endif
