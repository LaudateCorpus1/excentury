// File generated on Fri Aug 15, 2014 02:15:53 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
//Comment for sin_vector
void xc_help() {
    fprintf(stderr,
    "program: tools-sin_vector\n"
    "\ndescription:\n"
    "    Given a vector of values, it returns the sin of each of its\n"
    "    elements.\n"
    "\nparameters:\n"
    "    `v`: input vector\n"
    "    `w`: input vector\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    excentury::DynamicTensor<2, double> v; XC_DI_.dump(v, "v", v[0]);
    excentury::StaticTensor<2, 6, double> w(3, 2); XC_DI_.dump(w, "w", w[0]);
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Given a vector of values, it returns the sin of each of its
    elements.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    excentury::DynamicTensor<2, double> v; XC_LI_.load(v, v[0]);
    excentury::StaticTensor<2, 6, double> w(3, 2); XC_LI_.load(w, w[0]);
    XC_LI_.close();

    for (size_t i=0; i < v.dim(0); ++i) {
        for (size_t j=0; j < v.dim(1); ++j) {
            v(i, j) = sin(v(i, j));
        }
    }
    for (size_t i=0; i < w.dim(0); ++i) {
        for (size_t j=0; j < w.dim(1); ++j) {
            w(i, j) *= 2;
        }
    }

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(v, "v", v[0]);
    XC_DI_.dump(w, "w", w[0]);
    XC_DI_.close();
}
//Comment for test_rep epilog

