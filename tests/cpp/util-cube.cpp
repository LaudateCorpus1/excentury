// File generated on Wed Jan 22, 2014 02:27:27 AM by xcpp.
#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>
#include <objects.h>
// cube
void xc_help() {
    fprintf(stderr,
    "program: util-cube\n"
    "\ndescription:\n"
    "    cube a number\n"
    "\nparameters:\n"
    "    `x`: number to be cubed.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    int x(3); XC_DI_.dump(x, "x");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*cube a number*/
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
// EPILOG FOR THE WHOLE FILE
