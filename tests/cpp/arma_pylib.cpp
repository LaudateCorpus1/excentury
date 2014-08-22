// File generated on Fri Aug 22, 2014 10:40:26 AM by xcpp.
/*Armadillo Test

Collection of sample functions showing how to use the
[Armadillo](http://arma.sourceforge.net/) library.*/
#define XC_PYTHON
#include <armadillo>
#include <xc>

extern "C" {
    void inverse_det_py(size_t, char*, size_t&, char*&);
    void inverse_det_py_clear();
    void qr_py(size_t, char*, size_t&, char*&);
    void qr_py_clear();
    void solve_py(size_t, char*, size_t&, char*&);
    void solve_py_clear();

}

std::string inverse_det_py_str;
void inverse_det_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
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
    XC_DI_.dump(Ainv, "Ainv", Ainv(0, 0));
    XC_DI_.dump(d, "detA");
    XC_DI_.close();
    inverse_det_py_str = XC_DI_.str();
    ncout = inverse_det_py_str.size();
    pcout = (char*)inverse_det_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    inverse_det_py_str = run_error.msg;
    ncout = inverse_det_py_str.size();
    pcout = (char*)inverse_det_py_str.data();
}
}
void inverse_det_py_clear() {
    inverse_det_py_str.clear();
}

std::string qr_py_str;
void qr_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    arma::mat X(2, 2); XC_LI_.load(X, X(0,0));
    XC_LI_.close();

    arma::mat Q, R;
    int status = arma::qr(Q, R, X);

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(Q, "Q", Q(0, 0));
    XC_DI_.dump(R, "R", R(0, 0));
    XC_DI_.dump(status, "status");
    XC_DI_.close();
    qr_py_str = XC_DI_.str();
    ncout = qr_py_str.size();
    pcout = (char*)qr_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    qr_py_str = run_error.msg;
    ncout = qr_py_str.size();
    pcout = (char*)qr_py_str.data();
}
}
void qr_py_clear() {
    qr_py_str.clear();
}

std::string solve_py_str;
void solve_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    arma::mat A(2, 2); XC_LI_.load(A, A(0,0));
    arma::mat B(2, 2); XC_LI_.load(B, B(0,0));
    XC_LI_.close();

    arma::mat X;
    try {
        X = arma::solve(A,B);
    } catch (std::exception& run_error) {
        excentury::error(run_error.what());
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(X, "X", X(0, 0));
    XC_DI_.close();
    solve_py_str = XC_DI_.str();
    ncout = solve_py_str.size();
    pcout = (char*)solve_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    solve_py_str = run_error.msg;
    ncout = solve_py_str.size();
    pcout = (char*)solve_py_str.data();
}
}
void solve_py_clear() {
    solve_py_str.clear();
}

