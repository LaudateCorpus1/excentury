// File generated on Sat Feb 08, 2014 12:38:07 PM by xcpp.
#define XC_MATLAB
#include "mex.h"
//Comment before inclusion of excentury
#include <excentury/excentury.h>
//Comment for square_root
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    double x(2); XC_LI_.load(x);
    double x0(0); XC_LI_.load(x0);
    int iter(10); XC_LI_.load(iter);
    XC_LI_.close();

    if (x < 0) {
        excentury::error("input `x` must be non-negative");
    }
    excentury::timer tm;
    double a = x;
    x = x0;
    tm.tic();
    for (int i=0; i < iter; ++i) {
        x = x - (x*x - a)/(2.0*x);
    }
    tm.toc(true);
    tm.print_date("%c\n");

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(x, "ans");
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
//Comment for square_root epilog
