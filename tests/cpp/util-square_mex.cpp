// File generated on Fri Aug 15, 2014 02:38:41 AM by xcpp.
#define XC_MATLAB
#include <excentury/excentury.h>
#include <objects.h>
// square
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    double x(2); XC_LI_.load(x);
    XC_LI_.close();

    double result = x*x;

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(result, "result");
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
// EPILOG FOR THE WHOLE FILE
