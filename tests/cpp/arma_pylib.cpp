// File generated on Tue Apr 15, 2014 12:46:50 PM by xcpp.
/*Armadillo Test

Collection of sample functions showing how to use the
[Armadillo](http://arma.sourceforge.net/) library.*/
#define XC_PYTHON
#include <armadillo>
#include <excentury/excentury.h>
namespace excentury {
XC_DUMP_TEMPLATED_TENSOR(class elementType, arma::Mat<elementType>, m, m.mem[0]) {
    size_t ndims = 2;
    unsigned char rm = 0;
    XC_BYTE(rm);
    XC_SIZE(ndims);
    size_t size = m.n_elem;
    size_t dim[2] = {m.n_rows, m.n_cols};
    XC_ARRAY(dim, ndims);
    XC_ARRAY(m.mem, size);
}
XC_LOAD_TEMPLATED_TENSOR(class elementType, arma::Mat<elementType>, m) {
    size_t ndims;
    unsigned char rm;
    XC_BYTE(rm);
    if (rm != 0) {
        char msg[500];
        sprintf(msg, "Armadillo Mat::load:\n"
                "    RM mismatch, got %d, needs %d.", rm, 0);
        excentury::error(msg);
    }
    XC_SIZE(ndims);
    if (ndims != 2) {
        char msg[500];
        sprintf(msg, "Armadillo Mat::load:\n"
                "    dimension mismatch, needs dim = %d", 2);
        excentury::error(msg);
    }
    size_t* dim = new size_t[ndims];
    XC_ARRAY(dim, ndims);
    m.resize(dim[0], dim[1]);
    elementType* mem = const_cast<elementType*>(m.mem);
    XC_ARRAY(mem, m.n_elem);
    delete [] dim;
}
}

extern "C" {
    void ex1_py(size_t, char*, size_t&, char*&);
    void ex1_py_clear();

}

std::string ex1_py_str;
void ex1_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    arma::mat A(2, 2); XC_LI_.load(A, A(0,0));
    XC_LI_.close();

    double d = det(A);
    arma::mat Ainv;
    try {
        Ainv = inv(A);
    } catch (std::runtime_error& run_error) {
        excentury::error(run_error.what());
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(d, "detA");
    XC_DI_.dump(Ainv, "Ainv", Ainv(0, 0));
    XC_DI_.close();
    ex1_py_str = XC_DI_.str();
    ncout = ex1_py_str.size();
    pcout = (char*)ex1_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    ncout = run_error.size();
    pcout = (char*)run_error.c_str();
}
}
void ex1_py_clear() {
    ex1_py_str.clear();
}

