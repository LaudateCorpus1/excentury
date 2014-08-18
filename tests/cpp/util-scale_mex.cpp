// File generated on Fri Aug 15, 2014 02:43:55 AM by xcpp.
#define XC_MATLAB
#include <excentury/excentury.h>
#include <objects.h>
// scale
void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    size_t ncin_ = mxGetScalar(prhs[0]);
    char* pcin_ = mxArrayToString(prhs[1]);
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin_, ncin_);
    std::vector<double> v; XC_LI_.load(v, v[0]);
    double alpha; XC_LI_.load(alpha);
    XC_LI_.close();

    for (unsigned int i=0; i < v.size(); ++i) {
        v[i] *= alpha;
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
// epilog for scale
// EPILOG FOR THE WHOLE FILE
