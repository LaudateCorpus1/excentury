/** DYNAMICTENSOR.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: July 10, 2012
% Last Modified: November 21, 2013
*/

#ifndef XC_DYNAMICTENSOR_H
#define XC_DYNAMICTENSOR_H

// Macro to LOAD a DynamicTensor of dim 1
#define XC_LOAD_TEMPLATED_TENSOR_DIM_1 \
    size_t ndims; \
    unsigned char rm; \
    XC_BYTE(rm); \
    XC_SIZE(ndims); \
    if (ndims != 1) { \
        char msg[500]; \
        sprintf(msg, "DynamicTensor::load('%s'): \n" \
                "    dimension mismatch, needs dim = 1", varname); \
        excentury::error(msg); \
    } \
    size_t size; \
    XC_ARRAY(&size, ndims); \
    t.resize(size); \
    XC_ARRAY(t.data(), t.size())

// Macro to LOAD a DynamicTensor of dim N > 1
#define XC_LOAD_TEMPLATED_TENSOR_DIM_N \
    size_t ndims; \
    unsigned char rm; \
    XC_BYTE(rm); \
    if (rm != RM) { \
        char msg[500]; \
        sprintf(msg, "DynamicTensor::load:\n" \
                "    RM mismatch, needs RM = %d", RM); \
        excentury::error(msg); \
    } \
    XC_SIZE(ndims); \
    if (ndims != t.ndims()) { \
        char msg[500]; \
        sprintf(msg, "DynamicTensor::load:\n" \
                "    dimension mismatch, needs dim = %d", t.ndims()); \
        excentury::error(msg); \
    } \
    size_t* dim = new size_t[ndims]; \
    XC_ARRAY(dim, ndims); \
    t.resize(dim); \
    XC_ARRAY(t.data(), t.size((ndims-1)*(1-RM)+index)); \
    delete [] dim

// The following shows up quite a lot
#define XC_EIR elementType, index, RM

namespace excentury {

// GENERAL TENSOR
#undef XC_OBJECT
#undef XC_TMP_ARG
#define XC_OBJECT DynamicTensor<ndim, XC_EIR>
#define XC_TMP_ARG unsigned int ndim, class elementType, int index, int RM
template<unsigned int ndim, class elementType=double, int index=0, int RM=0>
class DynamicTensor: public Tensor<XC_OBJECT, ndim, XC_EIR>  {
public:
    DynamicTensor(): Tensor<DynamicTensor, ndim, XC_EIR>() {
        size_t dim[ndim];
        for (size_t i=0; i < ndim; ++i) dim[i] = 0;
        this->_set_dimensions(dim);
        try {
            this->_val = new elementType[1];
        } catch (const std::exception& e) {
            excentury::error("DynamicTensor(): failed to allocate memory");
        }
    }
    DynamicTensor(size_t *dim_): Tensor<DynamicTensor, ndim, XC_EIR>(dim_) {
        size_t total = 1;
        for (size_t i=0; i < ndim; ++i) {
            total *= dim_[i];
        }
        try {
            this->_val = new elementType[total];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor(*dim_):\n"
                    "    failed to allocate %zd objects.", total);
            excentury::error(msg);
        }
    }
    ~DynamicTensor() {
        if (this->_val != NULL) {
            delete [] this->_val;
            this->_val = NULL;
        }
    }
    void resize(size_t *dim_) {
        this->~DynamicTensor();
        this->_set_dimensions(dim_);
        size_t total = 1;
        for (size_t i=0; i < ndim; ++i) {
            total *= dim_[i];
        }
        try {
            this->_val = new elementType[total];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor::resize(*dim_):\n"
                    "    failed to allocate %zd objects.", total);
            excentury::error(msg);
        }
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
#define XC_OBJECT DynamicTensor<1, XC_EIR>
#define XC_TMP_ARG class elementType, int index, int RM
template<XC_TMP_ARG>
class XC_OBJECT: public Tensor<XC_OBJECT, 1, XC_EIR> {
public:
    DynamicTensor(): Tensor<DynamicTensor, 1, XC_EIR>(1) {
        try {
            this->_val = new elementType[1];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<1>():\n"
                    "    failed to allocate 1 object.");
            excentury::error(msg);
        }
    }
    DynamicTensor(size_t len_): Tensor<DynamicTensor, 1, XC_EIR>(len_) {
        try {
            this->_val = new elementType[len_];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<1>(len_):\n"
                    "    failed to allocate %zd objects.", len_);
            excentury::error(msg);
        }
    }
    ~DynamicTensor() {
        if (this->_val != NULL) {
            delete [] this->_val;
            this->_val = NULL;
        }
    }
    void resize(size_t len_) {
        this->~DynamicTensor();
        this->_set_dimensions(len_);
        try {
            this->_val = new elementType[len_];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<1>::resize(len_):\n"
                    "    failed to allocate %zd objects.", len_);
            excentury::error(msg);
        }
    }
    void resize(size_t *dim_) {
        resize(dim_[0]);
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
#define XC_OBJECT DynamicTensor<2, XC_EIR>
template<XC_TMP_ARG>
class XC_OBJECT: public Tensor<XC_OBJECT, 2, XC_EIR> {
public:
    DynamicTensor(): Tensor<DynamicTensor, 2, XC_EIR>(1, 1) {
        try {
            this->_val = new elementType[1];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<2>():\n"
                    "    failed to allocate 1 object.");
            excentury::error(msg);
        }
    }
    DynamicTensor(size_t d1_, size_t d2_):
        Tensor<DynamicTensor, 2, XC_EIR>(d1_, d2_) {
        try {
            this->_val = new elementType[d1_*d2_];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<2>(d1, d2):\n"
                    "    failed to allocate %zd objects.", d1_*d2_);
            excentury::error(msg);
        }
    }
    ~DynamicTensor() {
        if (this->_val != NULL) {
            delete [] this->_val;
            this->_val = NULL;
        }
    }
    void resize(size_t d1_, size_t d2_) {
        this->~DynamicTensor();
        this->_set_dimensions(d1_, d2_);
        try {
            this->_val = new elementType[d1_*d2_];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<2>::resize(d1, d2):\n"
                    "    failed to allocate %zd objects.", d1_*d2_);
            excentury::error(msg);
        }
    }
    void resize(size_t *dim_) {
        resize(dim_[0], dim_[1]);
    }
};
XC_DUMP_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t, t[index]) {
    XC_DUMP_TEMPLATED_TENSOR_DIM_N;
}
XC_LOAD_TEMPLATED_TENSOR(XC_TMP_ARG, XC_OBJECT, t) {
    XC_LOAD_TEMPLATED_TENSOR_DIM_N;
}


// TENSOR DIM 3
#undef XC_OBJECT
#define XC_OBJECT DynamicTensor<3, XC_EIR>
template<XC_TMP_ARG>
class XC_OBJECT: public Tensor<XC_OBJECT, 3, XC_EIR> {
public:
    DynamicTensor(): Tensor<DynamicTensor, 3, XC_EIR>(1, 1, 1) {
        try {
            this->_val = new elementType[1];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<3>():\n"
                    "    failed to allocate 1 object.");
            excentury::error(msg);
        }
    }
    DynamicTensor(size_t d1_, size_t d2_, size_t d3_):
        Tensor<DynamicTensor, 3, XC_EIR>(d1_, d2_, d3_) {
        try {
            this->_val = new elementType[d1_*d2_*d3_];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<3>(d1, d2, d3):\n"
                    "    failed to allocate %zd objects.", d1_*d2_*d3_);
            excentury::error(msg);
        }
    }
    ~DynamicTensor() {
        if (this->_val != NULL) {
            delete [] this->_val;
            this->_val = NULL;
        }
    }
    void resize(size_t d1_, size_t d2_, size_t d3_) {
        this->~DynamicTensor();
        this->_set_dimensions(d1_, d2_, d3_);
        try {
            this->_val = new elementType[d1_*d2_*d3_];
        } catch (const std::exception& e) {
            char msg[500];
            sprintf(msg, "DynamicTensor<3>(d1, d2, d3):\n"
                    "    failed to allocate %zd objects.", d1_*d2_*d3_);
            excentury::error(msg);
        }
    }
    void resize(size_t *dim_) {
        resize(dim_[0], dim_[1], dim_[2]);
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
