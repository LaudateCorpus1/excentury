// File generated on Mon Apr 07, 2014 01:31:31 AM by xcpp.
//Comment before inclusion of excentury
#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>
//Comment for rand_array
void xc_help() {
    fprintf(stderr,
    "program: tools-rand_array\n"
    "\ndescription:\n"
    "    Get an array of random numbers from a uniform distribution.\n"
    "\nparameters:\n"
    "    `n`: amount of random numbers.\n"
    "    `mean`: the mean of the distribution.\n"
    "    `std`: the standard deviation of the distribution.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    int n(10); XC_DI_.dump(n, "n");
    double mean(0); XC_DI_.dump(mean, "mean");
    double std(1); XC_DI_.dump(std, "std");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Get an array of random numbers from a uniform distribution.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    int n(10); XC_LI_.load(n);
    double mean(0); XC_LI_.load(mean);
    double std(1); XC_LI_.load(std);
    XC_LI_.close();

    excentury::MTRand rg;
    std::vector<double> val(n);
    for (int i=0; i < n; ++i) {
        val[i] = excentury::uniform_rand(rg, mean, std);
    }

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.dump(val, "val");
    XC_DI_.close();
}
//Comment for rand_array epilog

