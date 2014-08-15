// File generated on Fri Aug 15, 2014 02:15:50 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
//Comment for square_root
void xc_help() {
    fprintf(stderr,
    "program: tools-square_root\n"
    "\ndescription:\n"
    "    Compute the square root of a number using Newton's method.\n"
    "    This function will print to stdout the amount of time it took to\n"
    "    execute.\n"
    "\nparameters:\n"
    "    `x`: the input to the square root function.\n"
    "    `x0`: initial guess.\n"
    "    `iter`: number of iterations.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    double x(2); XC_DI_.dump(x, "x");
    double x0(0); XC_DI_.dump(x0, "x0");
    int iter(10); XC_DI_.dump(iter, "iter");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Compute the square root of a number using Newton's method.
    This function will print to stdout the amount of time it took to
    execute.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    double x(2); XC_LI_.load(x);
    double x0(0); XC_LI_.load(x0);
    int iter(10); XC_LI_.load(iter);
    XC_LI_.close();

    if (x < 0) {
        excentury::error("input `x` must be non-negative");
    }
    excentury::timer tm;
    double a = x;
    x = x0;
    tm.tic();
    for (int i=0; i < iter; ++i) {
        x = x - (x*x - a)/(2.0*x);
    }
    tm.toc(true);
    tm.print_date("%c\n");

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(x, "ans");
    XC_DI_.close();
}
//Comment for square_root epilog

