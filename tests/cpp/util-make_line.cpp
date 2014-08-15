// File generated on Fri Aug 15, 2014 02:18:11 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
#include <objects.h>
// make_line
void xc_help() {
    fprintf(stderr,
    "program: util-make_line\n"
    "\ndescription:\n"
    "    Given two points, it constructs a line.\n"
    "\nparameters:\n"
    "    `p1`: the first point.\n"
    "    `p2`: the second point.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    Point p1; XC_DI_.dump(p1, "p1");
    Point p2; XC_DI_.dump(p2, "p2");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Given two points, it constructs a line.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    Point p1; XC_LI_.load(p1);
    Point p2; XC_LI_.load(p2);
    XC_LI_.close();

    Line l(p1.x, p1.y, p2.x, p2.y);

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(l, "l");
    XC_DI_.close();
}
// EPILOG FOR THE WHOLE FILE
