// File generated on Sat Aug 16, 2014 03:32:41 PM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
void xc_help() {
    fprintf(stderr,
    "program: xc_test-timestwo\n"
    "\ndescription:\n"
    "    Take a scalar and double it.\n"
    "\nparameters:\n"
    "    `x`: scalar to be doubled.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    double x(2); XC_DI_.dump(x, "x");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Take a scalar and double it.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    double x(2); XC_LI_.load(x);
    XC_LI_.close();

    double result = 2*x;

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(result, "result");
    XC_DI_.close();
}

