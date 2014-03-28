// File generated on Mon Jan 06, 2014 01:10:03 PM by xcpp.
/*Util

This collection of functions demostrate how to create functions
compatible with python and cpp.*/
#include "mathlink.h"

#include <excentury/excentury.h>
#include <objects.h>
// square
void square() {
    /*return the square of the number.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    double x(2); XC_LI_.load(x);
    XC_LI_.close();

    double result = x*x;

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(result, "result");
    XC_DI_.close();
}

// cube
void cube() {
    /*cube a number*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    int x(3); XC_LI_.load(x);
    XC_LI_.close();

    int result = x*x*x;

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(result, "result");
    XC_DI_.close();
}

// move_point
void movePoint() {
    /*Adds a number to each of the coordinates of a point.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    Point p; XC_LI_.load(p);
    double x(1); XC_LI_.load(x);
    XC_LI_.close();

    p.x += x;
    p.y += x;

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(p, "p");
    XC_DI_.close();
}

// make_line
void makeLine() {
    /*Given two points, it constructs a line.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    Point p1; XC_LI_.load(p1);
    Point p2; XC_LI_.load(p2);
    XC_LI_.close();

    Line l(p1.x, p1.y, p2.x, p2.y);

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(l, "l");
    XC_DI_.close();
}

// scale
void scale() {
    /*Scalar multiplication.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    std::vector<double> v; XC_LI_.load(v);
    double alpha; XC_LI_.load(alpha);
    XC_LI_.close();

    for (int i=0; i < v.size(); ++i) {
        v[i] *= alpha;
    }

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v, "v");
    XC_DI_.close();
}
// epilog for scale

// print_msg
void printMsg() {
    /*Print a message to the standard error stream.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    std::string msg; XC_LI_.load(msg);
    XC_LI_.close();

    fprintf(stderr, "%s\n", msg.c_str());

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    
    XC_DI_.close();
}

// gen_tensors
void genTensors() {
    /*Generate tensors of dimension 4.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    XC_LI_.close();

    size_t size[4] = {2, 3, 4, 5};
    excentury::dynamicTensor<4, double, 0, 0> v1(size);
    excentury::dynamicTensor<4, double, 0, 1> v2(size);
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

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v1, "v1");
    XC_DI_.dump(v2, "v2");
    XC_DI_.close();
}

// scale_array
void scaleArray() {
    /*scale a one dimentional array.*/
    excentury::MLInterface<excentury::load_mode> XC_LI_;
    excentury::dynamicTensor<1, double, 0, 1> v; XC_LI_.load(v);
    double s; XC_LI_.load(s);
    XC_LI_.close();

    for (int i=0; i < v.dim(); ++i) {
        v[i] *= s;
    }

    excentury::MLInterface<excentury::dump_mode> XC_DI_;
    XC_DI_.dump(v, "v");
    XC_DI_.close();
}
// epilog for scale_array

int main(int argc, char* argv[]) {
    return MLMain(argc, argv);
}
// EPILOG FOR THE WHOLE FILE
