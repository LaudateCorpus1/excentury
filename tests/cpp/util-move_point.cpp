// File generated on Fri Aug 15, 2014 02:18:10 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
#include <objects.h>
// move_point
void xc_help() {
    fprintf(stderr,
    "program: util-move_point\n"
    "\ndescription:\n"
    "    Adds a number to each of the coordinates of a point.\n"
    "\nparameters:\n"
    "    `p`: the point to be moved.\n"
    "    `x`: the amount the point should be moved.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    Point p; XC_DI_.dump(p, "p");
    double x(1); XC_DI_.dump(x, "x");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Adds a number to each of the coordinates of a point.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    Point p; XC_LI_.load(p);
    double x(1); XC_LI_.load(x);
    XC_LI_.close();

    p.x += x;
    p.y += x;

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(p, "p");
    XC_DI_.close();
}
// EPILOG FOR THE WHOLE FILE
