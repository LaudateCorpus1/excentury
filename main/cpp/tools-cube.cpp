// File generated on Tue Dec 10, 2013 09:57:12 PM by xcpp.
#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>

void xc_help() {
    fprintf(stderr,
    "program: tools-cube\n"
    "\ndescription:\n"
    "    cube a number\n"
    "\nparameters:\n"
    "    x: number to be cubed.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::textInterface<excentury::dump_mode> __XC_DI__(stdout);
    int x(3); __XC_DI__.dump(x, "x");
    __XC_DI__.close();
}
int main(int argc, char** argv) {
    /*cube a number*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::stextInterface<excentury::load_mode> __XC_LI__(argv[1]);
    int x(3); __XC_LI__.load(x);
    __XC_LI__.close();

    int result = x*x*x;

    excentury::textInterface<excentury::dump_mode> __XC_DI__(stdout);
    __XC_DI__.dump(result, "result");
    __XC_DI__.close();
}
