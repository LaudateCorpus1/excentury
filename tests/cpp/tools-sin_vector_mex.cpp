// File generated on Fri Aug 15, 2014 03:24:10 AM by xcpp.
#define XC_MATLAB
#include <excentury/excentury.h>
//Comment for sin_vector
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    excentury::DynamicTensor<2, double> v; XC_LI_.load(v, v[0]);
    excentury::StaticTensor<2, 6, double> w(3, 2); XC_LI_.load(w, w[0]);
    XC_LI_.close();

    for (size_t i=0; i < v.dim(0); ++i) {
        for (size_t j=0; j < v.dim(1); ++j) {
            v(i, j) = sin(v(i, j));
        }
    }
    for (size_t i=0; i < w.dim(0); ++i) {
        for (size_t j=0; j < w.dim(1); ++j) {
            w(i, j) *= 2;
        }
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v, "v", v[0]);
    XC_DI_.dump(w, "w", w[0]);
    XC_DI_.close();
    std::string xc_mex_str_ = XC_DI_.str();
    plhs[0] = mxCreateDoubleMatrix(1, 1, mxREAL);
    double* ncout_ = mxGetPr(plhs[0]);
    ncout_[0] = xc_mex_str_.size();
    plhs[1] = mxCreateString(xc_mex_str_.data());
    mxFree(pcin_);
}
//Comment for test_rep epilog
