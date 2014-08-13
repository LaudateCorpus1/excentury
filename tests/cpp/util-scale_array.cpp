// File generated on Wed Apr 09, 2014 04:04:12 PM by xcpp.
#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>
#include <objects.h>
// scale_array
void xc_help() {
    fprintf(stderr,
    "program: util-scale_array\n"
    "\ndescription:\n"
    "    scale a one dimentional array.\n"
    "\nparameters:\n"
    "    `v`: the array to be scaled.\n"
    "    `s`: the scalar factor.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    excentury::DynamicTensor<1, double, 0, 1> v; XC_DI_.dump(v, "v", v[0]);
    double s; XC_DI_.dump(s, "s");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*scale a one dimentional array.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    excentury::DynamicTensor<1, double, 0, 1> v; XC_LI_.load(v, v[0]);
    double s; XC_LI_.load(s);
    XC_LI_.close();

    for (unsigned int i=0; i < v.dim(); ++i) {
        v[i] *= s;
    }

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(v, "v");
    XC_DI_.close();
}
// epilog for scale_array
// EPILOG FOR THE WHOLE FILE
