// File generated on Sat Aug 16, 2014 03:45:37 PM by xcpp.
/*XC TEST

This is a simple collection of functions to make sure that excentury
can compile and run the code from each of functions.*/
#define XC_PYTHON
#include <excentury/excentury.h>

extern "C" {
    void timestwo_py(size_t, char*, size_t&, char*&);
    void timestwo_py_clear();
    void cube_py(size_t, char*, size_t&, char*&);
    void cube_py_clear();

}

std::string timestwo_py_str;
void timestwo_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    double x(2); XC_LI_.load(x);
    XC_LI_.close();

    double result = 2*x;

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(result, "result");
    XC_DI_.close();
    timestwo_py_str = XC_DI_.str();
    ncout = timestwo_py_str.size();
    pcout = (char*)timestwo_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    timestwo_py_str = run_error.msg;
    ncout = timestwo_py_str.size();
    pcout = (char*)timestwo_py_str.data();
}
}
void timestwo_py_clear() {
    timestwo_py_str.clear();
}

std::string cube_py_str;
void cube_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    int x(3); XC_LI_.load(x);
    XC_LI_.close();

    int result = x*x*x;

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(result, "result");
    XC_DI_.close();
    cube_py_str = XC_DI_.str();
    ncout = cube_py_str.size();
    pcout = (char*)cube_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    cube_py_str = run_error.msg;
    ncout = cube_py_str.size();
    pcout = (char*)cube_py_str.data();
}
}
void cube_py_clear() {
    cube_py_str.clear();
}

