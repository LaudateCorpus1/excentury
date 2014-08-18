// File generated on Sat Aug 16, 2014 03:32:42 PM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
void xc_help() {
    fprintf(stderr,
    "program: xc_test-cube\n"
    "\ndescription:\n"
    "    cube an integer\n"
    "\nparameters:\n"
    "    `x`: integer to be cubed.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    int x(3); XC_DI_.dump(x, "x");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*cube an integer*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    int x(3); XC_LI_.load(x);
    XC_LI_.close();

    int result = x*x*x;

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(result, "result");
    XC_DI_.close();
}

