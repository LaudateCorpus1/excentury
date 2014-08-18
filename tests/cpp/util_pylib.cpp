// File generated on Fri Aug 15, 2014 01:50:36 AM by xcpp.
/*Util

This collection of functions demostrate how to create functions
compatible with python and cpp.*/
#define XC_PYTHON
#include <excentury/excentury.h>
#include <objects.h>

extern "C" {
    void square_py(size_t, char*, size_t&, char*&);
    void square_py_clear();
    void cube_py(size_t, char*, size_t&, char*&);
    void cube_py_clear();
    void move_point_py(size_t, char*, size_t&, char*&);
    void move_point_py_clear();
    void make_line_py(size_t, char*, size_t&, char*&);
    void make_line_py_clear();
    void scale_py(size_t, char*, size_t&, char*&);
    void scale_py_clear();
    void print_msg_py(size_t, char*, size_t&, char*&);
    void print_msg_py_clear();
    void gen_tensors_py(size_t, char*, size_t&, char*&);
    void gen_tensors_py_clear();
    void scale_array_py(size_t, char*, size_t&, char*&);
    void scale_array_py_clear();

}

// square
std::string square_py_str;
void square_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    double x(2); XC_LI_.load(x);
    XC_LI_.close();

    double result = x*x;

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(result, "result");
    XC_DI_.close();
    square_py_str = XC_DI_.str();
    ncout = square_py_str.size();
    pcout = (char*)square_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    square_py_str = run_error.msg;
    ncout = square_py_str.size();
    pcout = (char*)square_py_str.data();
}
}
void square_py_clear() {
    square_py_str.clear();
}

// cube
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

// move_point
std::string move_point_py_str;
void move_point_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    Point p; XC_LI_.load(p);
    double x(1); XC_LI_.load(x);
    XC_LI_.close();

    p.x += x;
    p.y += x;

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(p, "p");
    XC_DI_.close();
    move_point_py_str = XC_DI_.str();
    ncout = move_point_py_str.size();
    pcout = (char*)move_point_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    move_point_py_str = run_error.msg;
    ncout = move_point_py_str.size();
    pcout = (char*)move_point_py_str.data();
}
}
void move_point_py_clear() {
    move_point_py_str.clear();
}

// make_line
std::string make_line_py_str;
void make_line_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    Point p1; XC_LI_.load(p1);
    Point p2; XC_LI_.load(p2);
    XC_LI_.close();

    Line l(p1.x, p1.y, p2.x, p2.y);

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(l, "l");
    XC_DI_.close();
    make_line_py_str = XC_DI_.str();
    ncout = make_line_py_str.size();
    pcout = (char*)make_line_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    make_line_py_str = run_error.msg;
    ncout = make_line_py_str.size();
    pcout = (char*)make_line_py_str.data();
}
}
void make_line_py_clear() {
    make_line_py_str.clear();
}

// scale
std::string scale_py_str;
void scale_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    std::vector<double> v; XC_LI_.load(v, v[0]);
    double alpha; XC_LI_.load(alpha);
    XC_LI_.close();

    for (unsigned int i=0; i < v.size(); ++i) {
        v[i] *= alpha;
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v, "v");
    XC_DI_.close();
    scale_py_str = XC_DI_.str();
    ncout = scale_py_str.size();
    pcout = (char*)scale_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    scale_py_str = run_error.msg;
    ncout = scale_py_str.size();
    pcout = (char*)scale_py_str.data();
}
}
void scale_py_clear() {
    scale_py_str.clear();
}
// epilog for scale

// print_msg
std::string print_msg_py_str;
void print_msg_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    std::string msg; XC_LI_.load(msg);
    XC_LI_.close();

    fprintf(stderr, "%s\n", msg.c_str());

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    
    XC_DI_.close();
    print_msg_py_str = XC_DI_.str();
    ncout = print_msg_py_str.size();
    pcout = (char*)print_msg_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    print_msg_py_str = run_error.msg;
    ncout = print_msg_py_str.size();
    pcout = (char*)print_msg_py_str.data();
}
}
void print_msg_py_clear() {
    print_msg_py_str.clear();
}

// gen_tensors
std::string gen_tensors_py_str;
void gen_tensors_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
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
    gen_tensors_py_str = XC_DI_.str();
    ncout = gen_tensors_py_str.size();
    pcout = (char*)gen_tensors_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    gen_tensors_py_str = run_error.msg;
    ncout = gen_tensors_py_str.size();
    pcout = (char*)gen_tensors_py_str.data();
}
}
void gen_tensors_py_clear() {
    gen_tensors_py_str.clear();
}

// scale_array
std::string scale_array_py_str;
void scale_array_py(size_t ncin, char* pcin, size_t& ncout, char*& pcout) {
try {
    excentury::STextInterface<excentury::load_mode> XC_LI_(pcin, ncin);
    excentury::DynamicTensor<1, double, 0, 1> v; XC_LI_.load(v, v[0]);
    double s; XC_LI_.load(s);
    XC_LI_.close();

    for (unsigned int i=0; i < v.dim(); ++i) {
        v[i] *= s;
    }

    excentury::STextInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v, "v");
    XC_DI_.close();
    scale_array_py_str = XC_DI_.str();
    ncout = scale_array_py_str.size();
    pcout = (char*)scale_array_py_str.data();
} catch (excentury::RuntimeError& run_error) {
    scale_array_py_str = run_error.msg;
    ncout = scale_array_py_str.size();
    pcout = (char*)scale_array_py_str.data();
}
}
void scale_array_py_clear() {
    scale_array_py_str.clear();
}
// epilog for scale_array

// EPILOG FOR THE WHOLE FILE
