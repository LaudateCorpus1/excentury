// File generated on Fri Aug 15, 2014 02:18:08 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
#include <objects.h>
// square
void xc_help() {
    fprintf(stderr,
    "program: util-square\n"
    "\ndescription:\n"
    "    return the square of the number.\n"
    "\nparameters:\n"
    "    `x`: number to be squared.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    double x(2); XC_DI_.dump(x, "x");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*return the square of the number.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    double x(2); XC_LI_.load(x);
    XC_LI_.close();

    double result = x*x;

    excentury::TextInterface<excentury::dump_mode> XC_DI_("tmp.txt");
    XC_DI_.dump(result, "result");
    XC_DI_.close();
}
// EPILOG FOR THE WHOLE FILE
