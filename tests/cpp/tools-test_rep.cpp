// File generated on Fri Aug 15, 2014 02:15:52 AM by xcpp.
#define XC_CPP
#include <excentury/excentury.h>
//Comment for test_rep
void xc_help() {
    fprintf(stderr,
    "program: tools-test_rep\n"
    "\ndescription:\n"
    "    This function will do useless computation for the sake of\n"
    "    testing the reporter object which will print messages to\n"
    "    stdout.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*This function will do useless computation for the sake of
    testing the reporter object which will print messages to
    stdout.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    XC_LI_.close();

    int a = 0;
    printf("A = %d\n", a);
    class sim_reporter: public excentury::Reporter {
    public:
        const int& a;
        sim_reporter(int& a_):
            a(a_),
            excentury::Reporter(10, stdout)
        {}
        void report() {
            fprintf(fp, "Value of a = %d\n", this->a);
        }
    };
    sim_reporter rep(a);
    for (int i=0; i < 10000; ++i) {
        for (int j=0; j < 100000; ++j) {
            for (int k =0; k < 1000; ++k) {
                a = i+j+k;
            }
        }
    }
    rep.end_report(); // Can be omitted
    printf("A = %d\n", a);

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    
    XC_DI_.close();
}
//Comment for test_rep epilog

