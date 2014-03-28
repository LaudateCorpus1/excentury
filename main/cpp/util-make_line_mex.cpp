// File generated on Wed Jan 22, 2014 02:27:58 AM by xcpp.
#include "mex.h"
#include <excentury/excentury.h>
#include <objects.h>
// make_line
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    Point p1; XC_LI_.load(p1);
    Point p2; XC_LI_.load(p2);
    XC_LI_.close();

    Line l(p1.x, p1.y, p2.x, p2.y);

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(l, "l");
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
// EPILOG FOR THE WHOLE FILE
