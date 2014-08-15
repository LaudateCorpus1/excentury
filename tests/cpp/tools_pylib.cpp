// File generated on Fri Aug 15, 2014 01:41:17 AM by xcpp.
/*Tools

This collection of functions are examples of how to use the objects
in excentury/tools.*/
#define XC_PYTHON
#include <excentury/excentury.h>

extern "C" {
    void square_root_py(size_t, char*, size_t&, char*&);
    void square_root_py_clear();
    void rand_array_py(size_t, char*, size_t&, char*&);
    void rand_array_py_clear();
    void test_rep_py(size_t, char*, size_t&, char*&);
    void test_rep_py_clear();
    void sin_vector_py(size_t, char*, size_t&, char*&);
    void sin_vector_py_clear();

}

//Comment for square_root
std::string square_root_py_str;
void square_root_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
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
    square_root_py_str = XC_DI_.str();
    ncout = square_root_py_str.size();
    pcout = (char*)square_root_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    square_root_py_str = run_error.msg;
    ncout = square_root_py_str.size();
    pcout = (char*)square_root_py_str.data();
}
}
void square_root_py_clear() {
    square_root_py_str.clear();
}
//Comment for square_root epilog

//Comment for rand_array
std::string rand_array_py_str;
void rand_array_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
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
    rand_array_py_str = XC_DI_.str();
    ncout = rand_array_py_str.size();
    pcout = (char*)rand_array_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    rand_array_py_str = run_error.msg;
    ncout = rand_array_py_str.size();
    pcout = (char*)rand_array_py_str.data();
}
}
void rand_array_py_clear() {
    rand_array_py_str.clear();
}
//Comment for rand_array epilog

//Comment for test_rep
std::string test_rep_py_str;
void test_rep_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    XC_LI_.close();

    int a = 0;
    printf("A = %d\n", a);
    class sim_reporter: public excentury::Reporter {
    public:
        const int& a;
        sim_reporter(int& a_):
            a(a_),
            excentury::Reporter(10, stdout)
        {}
        void report() {
            fprintf(fp, "Value of a = %d\n", this->a);
        }
    };
    sim_reporter rep(a);
    for (int i=0; i < 10000; ++i) {
        for (int j=0; j < 100000; ++j) {
            for (int k =0; k < 1000; ++k) {
                a = i+j+k;
            }
        }
    }
    rep.end_report(); // Can be omitted
    printf("A = %d\n", a);

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    
    XC_DI_.close();
    test_rep_py_str = XC_DI_.str();
    ncout = test_rep_py_str.size();
    pcout = (char*)test_rep_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    test_rep_py_str = run_error.msg;
    ncout = test_rep_py_str.size();
    pcout = (char*)test_rep_py_str.data();
}
}
void test_rep_py_clear() {
    test_rep_py_str.clear();
}
//Comment for test_rep epilog

//Comment for sin_vector
std::string sin_vector_py_str;
void sin_vector_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
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
    sin_vector_py_str = XC_DI_.str();
    ncout = sin_vector_py_str.size();
    pcout = (char*)sin_vector_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    sin_vector_py_str = run_error.msg;
    ncout = sin_vector_py_str.size();
    pcout = (char*)sin_vector_py_str.data();
}
}
void sin_vector_py_clear() {
    sin_vector_py_str.clear();
}
//Comment for test_rep epilog

