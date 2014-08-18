/** STATICTENSOR.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: July 03, 2012
% Last Modified: November 21, 2013
*/

#ifndef XC_STATICTENSOR_H
#define XC_STATICTENSOR_H

// Macro to LOAD a StaticTensor of dim 1
#define XC_LOAD_TEMPLATED_TENSOR_DIM_1 \
    size_t ndims; \
    unsigned char rm; \
    XC_BYTE(rm); \
    XC_SIZE(ndims); \
    if (ndims != 1) { \
        char msg[500]; \
        sprintf(msg, "StaticTensor::load: \n" \
                "    dimension mismatch, needs dim = 1"); \
        excentury::error(msg); \
    } \
    size_t size; \
    XC_ARRAY(&size, ndims); \
    if (size != t.size()) { \
        char msg[500]; \
        sprintf(msg, "StaticTensor::load: \n" \
                "    size mismatch, needs size = %zd, " \
                "data claims to be %zd. ", t.size(), size); \
        excentury::error(msg); \
    } \
    XC_ARRAY(t.data(), t.size())

// Macro to LOAD a StaticTensor of dim N > 1
#define XC_LOAD_TEMPLATED_TENSOR_DIM_N \
    size_t ndims; \
    unsigned char rm; \
    XC_BYTE(rm); \
    if (rm != RM) { \
        char msg[500]; \
        sprintf(msg, "StaticTensor::load: \n" \
                "    RM mismatch, needs RM = %zd", RM); \
        excentury::error(msg); \
    } \
    XC_SIZE(ndims); \
    if (ndims != t.ndims()) { \
        char msg[500]; \
        sprintf(msg, "StaticTensor::load: \n" \
                "    dimension mismatch, needs dim = %zd", t.ndims()); \
        excentury::error(msg); \
    } \
    size_t size = 1; \
    size_t* dim = new size_t[ndims]; \
    XC_ARRAY(dim, ndims); \
    for (int i=0; i < ndims; ++i) { \
        size *= dim[i]; \
        if (dim[i] != t.dim(i)) { \
            char msg[500]; \
            sprintf(msg, "StaticTensor::load: \n" \
                    "    dim(%zd) mismatch, needs %zd, " \
                    "data claims to be %zd." \
                    , i, t.dim(i), dim[i]); \
            excentury::error(msg); \
        } \
    } \
    XC_ARRAY(t.data(), size); \
    delete [] dim

// The following shows up quite a lot
#define XC_EIR elementType, index, RM

namespace excentury {

// GENERAL TENSOR
#undef XC_OBJECT
#undef XC_TMP_ARG
#define XC_OBJECT StaticTensor<ndim, nelements, XC_EIR>
#define XC_TMP_ARG size_t ndim, size_t nelements, \
                   class elementType, size_t index, int RM
template<size_t ndim, size_t nelements,
         class elementType=double, size_t index=0, int RM=0>
class StaticTensor: public Tensor<XC_OBJECT, ndim, XC_EIR>  {
private:
    elementType __val[nelements];
public:
    StaticTensor(size_t *dim): Tensor<StaticTensor, ndim, XC_EIR>(dim) {
        size_t total = 1;
        for (size_t i=0; i < ndim; ++i) {
            total *= dim[i];
        }
        if (total != nelements) {
            char msg[500];
            sprintf(msg, "StaticTensor(dim):\n"
                    "    prod(dim) = %zd != %zd = nelements",
                    total, nelements);
            excentury::error(msg);
        }
        this->_val = __val;
    }
};
XC_DUMP_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t, t[index]) {
    XC_DUMP_TEMPLATED_TENSOR_DIM_N;
}
XC_LOAD_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t) {
    XC_LOAD_TEMPLATED_TENSOR_DIM_N;
}

// TENSOR DIM 1
#undef XC_OBJECT
#undef XC_TMP_ARG
#define XC_OBJECT StaticTensor<1, nelements, XC_EIR>
#define XC_TMP_ARG size_t nelements, class elementType, size_t index, int RM
template<XC_TMP_ARG>
class XC_OBJECT: public Tensor<XC_OBJECT, 1, XC_EIR> {
private:
    elementType __val[nelements];
public:
    StaticTensor(): Tensor<StaticTensor, 1, XC_EIR>(nelements) {
        this->_val = __val;
    }
    StaticTensor(size_t len_): Tensor<StaticTensor, 1, XC_EIR>(len_) {
        if (len_ != nelements) {
            char msg[500];
            sprintf(msg, "StaticTensor<1>(len):\n"
                    "    len = %zd != %zd = nelements",
                    len_, nelements);
            excentury::error(msg);
        }
        this->_val = __val;
    }
};
XC_DUMP_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t, t[index]) {
    XC_DUMP_TEMPLATED_TENSOR_DIM_1;
}
XC_LOAD_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t) {
    XC_LOAD_TEMPLATED_TENSOR_DIM_1;
}

// TENSOR DIM 2
#undef XC_OBJECT
#undef XC_TMP_ARG
#define XC_OBJECT StaticTensor<2, nelements, XC_EIR>
#define XC_TMP_ARG size_t nelements, class elementType, size_t index, int RM
template<XC_TMP_ARG>
class XC_OBJECT: public Tensor<XC_OBJECT, 2, XC_EIR> {
private:
    elementType __val[nelements];
public:
    StaticTensor(size_t d1_, size_t d2_):
        Tensor<StaticTensor, 2, XC_EIR>(d1_, d2_) {
        size_t total = d1_*d2_;
        if (total != nelements) {
            char msg[500];
            sprintf(msg, "StaticTensor<2>(d1, d2):\n"
                    "    prod(dim) = %zd != %zd = nelements",
                    total, nelements);
            excentury::error(msg);
        }
        this->_val = __val;
    }
};
XC_DUMP_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t, t[index]) {
    XC_DUMP_TEMPLATED_TENSOR_DIM_N;
}
XC_LOAD_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t) {
    XC_LOAD_TEMPLATED_TENSOR_DIM_N;
}
#undef XC_OBJECT
#undef XC_TMP_ARG

// TENSOR DIM 3
#define XC_OBJECT StaticTensor<3, nelements, XC_EIR>
#define XC_TMP_ARG size_t nelements, class elementType, size_t index, int RM
template<XC_TMP_ARG>
class XC_OBJECT: public Tensor<XC_OBJECT, 3, XC_EIR> {
private:
    elementType __val[nelements];
public:
    StaticTensor(size_t d1_, size_t d2_, size_t d3_):
        Tensor<StaticTensor, 3, XC_EIR>(d1_, d2_, d3_) {
        size_t total = d1_*d2_*d3_;
        if (total != nelements) {
            char msg[500];
            sprintf(msg, "StaticTensor<3>(d1, d2, d3):\n"
                    "    prod(dim) = %zd != %zd = nelements",
                    total, nelements);
            excentury::error(msg);
        }
        this->_val = __val;
    }
};
XC_DUMP_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t, t[index]) {
    XC_DUMP_TEMPLATED_TENSOR_DIM_N;
}
XC_LOAD_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t) {
    XC_LOAD_TEMPLATED_TENSOR_DIM_N;
}
}

#undef XC_EIR
#undef XC_OBJECT
#undef XC_TMP_ARG
#undef XC_LOAD_TEMPLATED_TENSOR_DIM_1
#undef XC_LOAD_TEMPLATED_TENSOR_DIM_N

#endif
