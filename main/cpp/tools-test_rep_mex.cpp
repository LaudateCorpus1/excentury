// File generated on Sat Feb 08, 2014 12:38:10 PM by xcpp.
#define XC_MATLAB
#include "mex.h"
//Comment before inclusion of excentury
#include <excentury/excentury.h>
//Comment for test_rep
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
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

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
//Comment for test_rep epilog
