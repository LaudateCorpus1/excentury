// File generated on Wed Jan 22, 2014 02:28:02 AM by xcpp.
#include "mex.h"
#include <excentury/excentury.h>
#include <objects.h>
// scale_array
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    excentury::dynamicTensor<1, double, 0, 1> v; XC_LI_.load(v, v[0]);
    double s; XC_LI_.load(s);
    XC_LI_.close();

    for (int i=0; i < v.dim(); ++i) {
        v[i] *= s;
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v, "v");
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
// epilog for scale_array
// EPILOG FOR THE WHOLE FILE
