// File generated on Mon Jan 06, 2014 01:10:32 PM by xcpp.
/*Tools

This collection of functions are examples of how to use the objects
in excentury/tools.*/
#include "mathlink.h"
//Comment before inclusion of excentury

#include <excentury/excentury.h>
#include <excentury/tools/reporter.h>
#include <excentury/tools/rand.h>
//Comment for square_root
void squareRoot() {
    /*Compute the square root of a number using Newton's method.
    This function will print to stdout the amount of time it took to
    execute.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    double x(2); XC_LI_.load(x);
    double x0(0); XC_LI_.load(x0);
    int iter(10); XC_LI_.load(iter);
    XC_LI_.close();

    excentury::timer tm;
    double a = x;
    x = x0;
    tm.tic();
    for (int i=0; i < iter; ++i) {
        x = x - (x*x - a)/(2.0*x);
    }
    tm.toc(true);
    tm.print_date("%c\n");

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(x, "ans");
    XC_DI_.close();
}
//Comment for square_root epilog

//Comment for rand_array
void randArray() {
    /*Get an array of random numbers from a uniform distribution.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    int n(10); XC_LI_.load(n);
    double mean(0); XC_LI_.load(mean);
    double std(1); XC_LI_.load(std);
    XC_LI_.close();

    excentury::mtRand rg;
    std::vector<double> val(n);
    for (int i=0; i < n; ++i) {
        val[i] = excentury::uniform_rand(rg, mean, std);
    }

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(val, "val");
    XC_DI_.close();
}
//Comment for rand_array epilog

//Comment for test_rep
void testRep() {
    /*This function will do useless computation for the sake of
    testing the reporter object which will print messages to
    stdout.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    XC_LI_.close();

    int a = 0;
    printf("A = %d\n", a);
    class sim_reporter: public excentury::reporter {
    public:
        const int& a;
        sim_reporter(int& a_):
            a(a_),
            excentury::reporter(10, stdout)
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

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    
    XC_DI_.close();
}
//Comment for test_rep epilog

int main(int argc, char* argv[]) {
    return MLMain(argc, argv);
}
