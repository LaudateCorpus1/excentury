// File generated on Fri Aug 15, 2014 03:24:08 AM by xcpp.
#define XC_MATLAB
#include <excentury/excentury.h>
//Comment for rand_array
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    int n(10); XC_LI_.load(n);
    double mean(0); XC_LI_.load(mean);
    double std(1); XC_LI_.load(std);
    XC_LI_.close();

    excentury::MTRand rg;
    std::vector<double> val(n);
    for (int i=0; i < n; ++i) {
        val[i] = excentury::uniform_rand(rg, mean, std);
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(val, "val");
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
//Comment for rand_array epilog
