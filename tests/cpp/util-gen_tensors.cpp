// File generated on Fri Aug 15, 2014 02:18:15 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
#include <objects.h>
// gen_tensors
void xc_help() {
    fprintf(stderr,
    "program: util-gen_tensors\n"
    "\ndescription:\n"
    "    Generate tensors of dimension 4.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Generate tensors of dimension 4.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    XC_LI_.close();

    size_t size[4] = {2, 3, 4, 5};
    excentury::DynamicTensor<4, double, 0, 0> v1(size);
    excentury::DynamicTensor<4, double, 0, 1> v2(size);
    for (int i=0; i < 120; ++i) {
        v1[i] = i;
        v2[i] = i;
    }
    size_t tmp1[4] = {1,1,1,1};
    size_t tmp2[4] = {1,2,3,4};
    printf("v1(1,1,1,1) = %g\n", v1(tmp1));
    printf("v1(1,2,3,4) = %g\n", v1(tmp2));
    printf("v2(1,1,1,1) = %g\n", v2(tmp1));
    printf("v2(1,2,3,4) = %g\n", v2(tmp2));

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(v1, "v1");
    XC_DI_.dump(v2, "v2");
    XC_DI_.close();
}
// EPILOG FOR THE WHOLE FILE
