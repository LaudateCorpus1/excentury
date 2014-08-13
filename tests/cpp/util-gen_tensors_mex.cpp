// File generated on Wed Apr 09, 2014 04:04:03 PM by xcpp.
#define XC_MATLAB
#include "mex.h"
#include <excentury/excentury.h>
#include <objects.h>
// gen_tensors
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
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

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v1, "v1");
    XC_DI_.dump(v2, "v2");
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
// EPILOG FOR THE WHOLE FILE
