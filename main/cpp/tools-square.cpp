// File generated on Tue Dec 10, 2013 09:57:11 PM by xcpp.
#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>

void xc_help() {
    fprintf(stderr,
    "program: tools-square\n"
    "\ndescription:\n"
    "    return the square of the number.\n"
    "\nparameters:\n"
    "    x: number to be squared.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::textInterface<excentury::dump_mode> __XC_DI__(stdout);
    double x(2); __XC_DI__.dump(x, "x");
    __XC_DI__.close();
}
int main(int argc, char** argv) {
    /*return the square of the number. */
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::stextInterface<excentury::load_mode> __XC_LI__(argv[1]);
    double x(2); __XC_LI__.load(x);
    __XC_LI__.close();

    double result = x*x;

    excentury::textInterface<excentury::dump_mode> __XC_DI__("tmp.txt");
    __XC_DI__.dump(result, "result");
    __XC_DI__.close();
}
