// File generated on Fri Aug 15, 2014 02:18:13 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
#include <objects.h>
// scale
void xc_help() {
    fprintf(stderr,
    "program: util-scale\n"
    "\ndescription:\n"
    "    Scalar multiplication.\n"
    "\nparameters:\n"
    "    `v`: the vector to multiply. \n"
    "    `alpha`: the scalar.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    std::vector<double> v; XC_DI_.dump(v, "v", v[0]);
    double alpha; XC_DI_.dump(alpha, "alpha");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Scalar multiplication.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    std::vector<double> v; XC_LI_.load(v, v[0]);
    double alpha; XC_LI_.load(alpha);
    XC_LI_.close();

    for (unsigned int i=0; i < v.size(); ++i) {
        v[i] *= alpha;
    }

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(v, "v");
    XC_DI_.close();
}
// epilog for scale
// EPILOG FOR THE WHOLE FILE
