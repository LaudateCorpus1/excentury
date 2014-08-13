/** TENSOR.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: July 03, 2012
% Last Modified: November 21, 2013
*/

#ifdef XC_TENSOR_DEBUG
#define DEBUGOFF XC_TENSOR_DEBUG
#include "../debugoff.h"
#endif

#ifndef TENSOR_H
#define TENSOR_H

#define XC_CHECK_INDEX_ERROR(var,bound) exitif( \
    var-index < 0 || var-index >= bound, \
    dbg_info(), \
    " " #var " = %d\n" \
    " index = %d\n" \
    " " #bound " = %zd\n\n" \
    " Valid values of " #var ": [%d, %zd]\n\n", \
    var, index, bound, index, bound-1+index)

#define XC_CHECK_IX_ERROR(var,bound,i) exitif( \
    var[i]-index < 0 || var[i]-index >= bound[i], \
    dbg_info(), \
    " " #var "[%d] = %d\n" \
    " index = %d\n" \
    " " #bound "[%d] = %d\n\n" \
    " Valid values of " #var "[%d]: [%d, %d]\n\n", \
    i, var[i], index, i, bound[i], i, index, bound[IX]-1+index)

namespace excentury {

template<class elementType, size_t index, int RM>
void print_matrix(std::ostream& out_, const elementType* v_,
                  const size_t* d_, const size_t *D_) {
    size_t i[2];
    out_ << " r \\ c | ";
    for (i[1] = index; i[1] < d_[1]+index; ++i[1]) {
        out_ << std::setw(8) << i[1] << " | ";
    }
    out_ << "\n-------+";
    for (i[1] = index; i[1] < d_[1]+index; ++i[1]) {
        out_ << std::setw(11) << "----------+";
    }
    out_ << "\n";
    for (i[0] = index; i[0] < d_[0]+index; ++i[0]) {
        out_ << std::setw(6) << i[0] << " | ";
        for (i[1] = index; i[1] < d_[1]+index; ++i[1]) {
            out_ << std::setw(8)
                 << v_[(i[RM]-index)+(i[1-RM]-index)*D_[RM]] << " | ";
        }
        out_ << "\n";
    }
}

template<size_t ndim, class elementType, size_t index, int RM>
void print_matrix_rm(std::ostream& out_, const elementType* v_,
                     const size_t* d_, const size_t *D_,
                     size_t level_, size_t *k) {
    if (level_ > 1) {
        for (size_t i = index; i < d_[0]+index; ++i) {
            k[0] = i;
            excentury::print_matrix_rm<ndim, elementType, index, RM>(
                out_, &v_[D_[1]*(i-index)], &d_[1], &D_[1], level_-1, &k[1]);
        }
        out_ << "\n";
    } else {
        out_ << "\ntensor(";
        // Note that k may not be the original that we started with.
        // notice that &k[1] is being passed recursively to the
        // function and thus it is ok to access negative indices.
        for (int j = -(ndim-2); j < 0; ++j) {
            out_ << k[j] << ",";
        }
        out_ << ":,:) = \n\n";
        excentury::print_matrix<elementType, index, RM>(out_, v_, d_, D_);
    }
}

template<size_t ndim, class elementType, size_t index, int RM>
void print_matrix_cm(std::ostream& out_, const elementType* v_,
                     const size_t* d_, const size_t *D_,
                     size_t level_, size_t *k)
{
    if (level_ > 1) {
        for (size_t i = index; i < d_[level_]+index; ++i) {
            k[level_-2] = i;
            excentury::print_matrix_cm<ndim, elementType, index, RM>(
                out_, &v_[D_[level_-1]*(i-index)], d_, D_, level_-1, k);
        }
        out_ << "\n";
    } else {
        out_ << "\ntensor(:,:,";
         for (size_t j = 0; j < ndim-2-1; ++j) {
            out_ << k[j] << ",";
        }
        out_ << k[ndim-2-1] << ") = \n\n";
        excentury::print_matrix<elementType, index, RM>(out_, v_, d_, D_);
    }
}

template<size_t dim, class AllocationType,
         class elementType, size_t index, int RM>
struct XCDisplay {
    template<class T>
    static void display(std::ostream& os, const T& t) {
        os << "XC_DISPLAY NOT OVERLOADED...\n";
    }
};
#define DEF_XC_DISPLAY(TYPE) \
    template<size_t dim, class AllocationType, size_t index, int RM> \
    struct XCDisplay<dim, AllocationType, TYPE, index, RM> { \
        static void display(std::ostream& os, const \
                Tensor<AllocationType, dim, TYPE, index, RM>& t) { \
            t.display(os); \
        } \
    };

// GENERAL TENSOR
template<class AllocationType, size_t ndim,
         class elementType=double, size_t index=0, int RM=0>
class Tensor {
private:
    size_t _dim[ndim];
    size_t _Dim[ndim];
    void resize(size_t* i) {
        static_cast<AllocationType*>(this)->resize(i);
    }
protected:
    elementType* _val;
    void _set_dimensions(size_t *dim_) {
        _dim[(ndim-1)*RM] = dim_[(ndim-1)*RM];
        _Dim[(ndim-1)*RM] = dim_[(ndim-1)*RM];
        for (size_t i=1; i < ndim; ++i) {
            _dim[(ndim-1-2*i)*RM+i] = dim_[(ndim-1-2*i)*RM+i];
            _Dim[(ndim-1-2*i)*RM+i] = _dim[(ndim-1-2*i)*RM+i]*
                                      _Dim[(ndim+1-2*i)*RM+(i-1)];
        }
    }
public:
    Tensor(): _val(NULL) {}
    Tensor(size_t *dim_): _val(NULL) {
        _dim[(ndim-1)*RM] = dim_[(ndim-1)*RM];
        _Dim[(ndim-1)*RM] = dim_[(ndim-1)*RM];
        for (size_t i=1; i < ndim; ++i) {
            _dim[(ndim-1-2*i)*RM+i] = dim_[(ndim-1-2*i)*RM+i];
            _Dim[(ndim-1-2*i)*RM+i] = _dim[(ndim-1-2*i)*RM+i]*
                                      _Dim[(ndim+1-2*i)*RM+(i-1)];
        }
    }
    elementType& operator[] (size_t i) {
        XC_CHECK_INDEX_ERROR(i, _Dim[(ndim-1)*(1-RM)]);
        return _val[i-index];
    }
    const elementType& operator[] (size_t i) const {
        XC_CHECK_INDEX_ERROR(i, _Dim[(ndim-1)*(1-RM)]);
        return _val[i-index];
    }
    #define IX0 ((ndim-1)*RM)
    #define IX ((ndim-1-2*k)*RM+k)
    elementType& operator() (size_t *i) {
        size_t k = 0;
        size_t offset = i[IX0]-index;
        XC_CHECK_IX_ERROR(i, _dim, IX0);
        for (k=1; k < ndim; ++k) {
            XC_CHECK_IX_ERROR(i, _dim, IX);
            offset += (i[IX]-index)*_Dim[(ndim+1-2*k)*RM+(k-1)];
        }
        return _val[offset];
    }
    const elementType& operator() (size_t *i) const {
        size_t k = 0;
        size_t offset = i[IX0]-index;
        XC_CHECK_IX_ERROR(i, _dim, IX0);
        for (k=1; k < ndim; ++k) {
            XC_CHECK_IX_ERROR(i, _dim, IX);
            offset += (i[IX]-index)*_Dim[(ndim+1-2*k)*RM+(k-1)];
        }
        return _val[offset];
    }
    #undef IX
    #undef IX0
    size_t ndims() const {
        return ndim;
    }
    const size_t& dim(size_t i) const {
        XC_CHECK_INDEX_ERROR(i, ndims());
        return _dim[i-index];
    }
    const size_t& size(size_t i) const {
        XC_CHECK_INDEX_ERROR(i, ndims());
        return _Dim[i-index];
    }
    elementType* data() const {
        return _val;
    }
    void display(std::ostream& out_) const {
        size_t k[ndim-2];
        if (RM == 0) {
            excentury::print_matrix_cm<ndim, elementType, index, RM>(
                out_, _val, _dim, _Dim, ndim-1, k);
        } else {
            excentury::print_matrix_rm<ndim, elementType, index, RM>(
                out_, _val, _dim, _Dim, ndim-1, k);
        }
    }
    void dbg_info() const {
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
        fprintf(stderr, "Tensor information: \n\n");
        fprintf(stderr, "ClassName      : ");
            XC_PRINT_CLASS_NAME(*(static_cast<const
            AllocationType*>(this))); fprintf(stderr, "\n");
        fprintf(stderr, "ElementType    : ");
            XC_PRINT_CLASS_NAME(elementType); fprintf(stderr, "\n");
        fprintf(stderr, "Index          : %d based index\n", index);
        fprintf(stderr, "RM             : %d "
                        "(1 is for row-major order, "
                        "0 is for column-major order)\n", RM);
        fprintf(stderr, "NDim           : %d\n", ndim);
        fprintf(stderr, "dim            : {");
        for (size_t i=0; i < ndim-1; ++i) {
            fprintf(stderr, "%d, ", _dim[i]);
        }
        fprintf(stderr, "%d}\n", _dim[ndim-1]);
        fprintf(stderr, "size           : {");
        for (size_t i=0; i < ndim-1; ++i) {
            fprintf(stderr, "%d, ", _Dim[i]);
        }
        fprintf(stderr, "%d}\n\n", _Dim[ndim-1]);
        fprintf(stderr, "\nMatrix Contents: \n\n");
        XCDisplay<ndim, AllocationType,
        elementType, index, RM>::display(std::cerr, *this);
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
    }
};

/* SPECIALIZATION FOR TENSOR OF DIMENSION 1 */
template<class AllocationType, class elementType, size_t index, int RM>
class Tensor<AllocationType, 1, elementType, index, RM> {
private:
    size_t _len;
    void resize(size_t len_) {
        static_cast<AllocationType*>(this)->resize(len_);
    }
    void resize(size_t *len_) {
        static_cast<AllocationType*>(this)->resize(len_[0]);
    }
protected:
    elementType* _val;
    void _set_dimensions(size_t len_) {
        _len = len_;
    }
    void _set_dimensions(size_t *len_) {
        _len = len_[0];
    }
public:
    Tensor(): _val(NULL) {}
    Tensor(size_t len_) : _val(NULL) {
        _len = len_;
    }
    elementType& operator[] (size_t i) {
        XC_CHECK_INDEX_ERROR(i, _len);
        return _val[i-index];
    }
    const elementType& operator[] (size_t i) const {
        XC_CHECK_INDEX_ERROR(i, _len);
        return _val[i-index];
    }
    elementType& operator() (size_t i) {
        XC_CHECK_INDEX_ERROR(i, _len);
        return _val[i-index];
    }
    const elementType& operator() (size_t i) const {
        XC_CHECK_INDEX_ERROR(i, _len);
        return _val[i-index];
    }
    elementType& operator() (size_t *i) {
        XC_CHECK_INDEX_ERROR(i[0], _len);
        return _val[i[0]-index];
    }
    const elementType& operator() (size_t *i) const {
        XC_CHECK_INDEX_ERROR(i[0], _len);
        return _val[i[0]-index];
    }
    const size_t ndims() const {
        return 1;
    }
    const size_t& dim() const {
        return _len;
    }
    const size_t& size() const {
        return _len;
    }
    elementType* data() const {
        return _val;
    }
    void display(std::ostream& out_) const {
        if (type(_val[0]) == 'S') {
            out_ << "Unable to print matrix of structs...\n";
        } else {
            for (size_t i = index; i < size()+index; ++i) {
                out_ << std::setw(8) << i << " | "
                    << std::setw(8) << _val[i-index] << "\n";
            }
        }
    }
    void dbg_info() const {
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
        fprintf(stderr, "Tensor information: \n\n");
        fprintf(stderr, "ClassName      : ");
            XC_PRINT_CLASS_NAME(*(static_cast<const
            AllocationType*>(this))); fprintf(stderr, "\n");
        fprintf(stderr, "ElementType    : ");
            XC_PRINT_CLASS_NAME(elementType); fprintf(stderr, "\n");
        fprintf(stderr, "Index          : %d based index\n", index);
        fprintf(stderr, "RM             : %d "
                        "(1 is for row-major order, "
                        "0 is for column-major order)\n", RM);
        fprintf(stderr, "NDim           : %d\n", 1);
        fprintf(stderr, "dim() = size() : %zd\n\n", dim());
        fprintf(stderr, "Elements in Tensor: \n\n");
        XCDisplay<1, AllocationType,
        elementType, index, RM>::display(std::cerr, *this);
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
    }
};

/* SPECIALIZATION FOR TENSOR OF DIMENSION 2 */
template<class AllocationType, class elementType, size_t index, int RM>
class Tensor<AllocationType, 2, elementType, index, RM> {
private:
    size_t _dim[2];
    size_t _Dim[2];
    void resize(size_t d1_, size_t d2_) {
        static_cast<AllocationType*>(this)->resize(d1_, d2_);
    }
    void resize(size_t* d_) {
        static_cast<AllocationType*>(this)->resize(d_[0], d_[1]);
    }
protected:
    elementType* _val;
    void _set_dimensions(size_t d1_, size_t d2_) {
        _dim[0]    = d1_;
        _dim[1]    = d2_;
        _Dim[RM]   = _dim[RM];
        _Dim[1-RM] = _dim[1-RM]*_Dim[RM];
    }
    void _set_dimensions(size_t* d_) {
        _dim[0]    = d_[0];
        _dim[1]    = d_[1];
        _Dim[RM]   = _dim[RM];
        _Dim[1-RM] = _dim[1-RM]*_Dim[RM];
    }
public:
    Tensor(): _val(NULL) {}
    Tensor(size_t d1_, size_t d2_) : _val(NULL) {
        _dim[0]    = d1_;
        _dim[1]    = d2_;
        _Dim[RM]   = _dim[RM];
        _Dim[1-RM] = _dim[1-RM]*_Dim[RM];
    }
    elementType& operator[] (size_t i) {
        XC_CHECK_INDEX_ERROR(i, _Dim[1-RM]);
        return _val[i-index];
    }
    const elementType& operator[] (size_t i) const {
        XC_CHECK_INDEX_ERROR(i, _Dim[1-RM]);
        return _val[i-index];
    }
    elementType& operator() (size_t i1, size_t i2) {
        XC_CHECK_INDEX_ERROR(i1, _dim[0]);
        XC_CHECK_INDEX_ERROR(i2, _dim[1]);
        size_t i[2] = {i1-index, i2-index};
        return _val[i[RM]+i[1-RM]*_Dim[RM]];
    }
    const elementType& operator() (size_t i1, size_t i2) const {
        XC_CHECK_INDEX_ERROR(i1, _dim[0]);
        XC_CHECK_INDEX_ERROR(i2, _dim[1]);
        size_t i[2] = {i1-index, i2-index};
        return _val[i[RM]+i[1-RM]*_Dim[RM]];
    }
    elementType& operator() (size_t *i) {
        XC_CHECK_INDEX_ERROR(i[0], _dim[0]);
        XC_CHECK_INDEX_ERROR(i[1], _dim[1]);
        return _val[(i[RM]-index)+(i[1-RM]-index)*_Dim[RM]];
    }
    const elementType& operator() (size_t *i) const {
        XC_CHECK_INDEX_ERROR(i[0], _dim[0]);
        XC_CHECK_INDEX_ERROR(i[1], _dim[1]);
        return _val[(i[RM]-index)+(i[1-RM]-index)*_Dim[RM]];
    }
    size_t ndims() const {
        return 2;
    }
    const size_t& dim(size_t i) const {
        XC_CHECK_INDEX_ERROR(i, ndims());
        return _dim[i-index];
    }
    const size_t& size(size_t i) const {
        XC_CHECK_INDEX_ERROR(i, ndims());
        return _Dim[i-index];
    }
    elementType* data() const {
        return _val;
    }
    void display(std::ostream& out_) const {
        excentury::print_matrix<elementType, index, RM>(
            out_, _val, _dim, _Dim);
    }
    void dbg_info() const {
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
        fprintf(stderr, "Tensor information: \n\n");
        fprintf(stderr, "ClassName      : ");
            XC_PRINT_CLASS_NAME(*(static_cast<const
            AllocationType*>(this))); fprintf(stderr, "\n");
        fprintf(stderr, "ElementType    : ");
            XC_PRINT_CLASS_NAME(elementType); fprintf(stderr, "\n");
        fprintf(stderr, "Index          : %d based index\n", index);
        fprintf(stderr, "RM             : %d "
                        "(1 is for row-major order, "
                        "0 is for column-major order)\n", RM);
        fprintf(stderr, "NDim           : %d\n", 2);
        fprintf(stderr, "dim            : {%zu, %zu}\n",
                _dim[0], _dim[1]);
        fprintf(stderr, "size           : {%zu, %zu}\n\n",
                _Dim[0], _Dim[1]);
        fprintf(stderr, "Matrix Contents: \n\n");
        XCDisplay<2, AllocationType,
        elementType, index, RM>::display(std::cerr, *this);
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
    }
};

/* SPECIALIZATION FOR TENSOR OF DIMENSION 3 */
template<class AllocationType, class elementType, size_t index, int RM>
class Tensor<AllocationType, 3, elementType, index, RM> {
private:
    size_t _dim[3];
    size_t _Dim[3];
    void resize(size_t d1_, size_t d2_, size_t d3_) {
        static_cast<AllocationType*>(this)->resize(d1_, d2_, d3_);
    }
    void resize(size_t* d_) {
        static_cast<AllocationType*>(this)->resize(d_[0], d_[1], d_[2]);
    }
protected:
    elementType* _val;
    void _set_dimensions(size_t d1_, size_t d2_, size_t d3_) {
        _dim[0]        = d1_;
        _dim[1]        = d2_;
        _dim[2]        = d3_;
        _Dim[2*RM]     = _dim[2*RM];
        _Dim[1]        = _dim[1]*_Dim[2*RM];
        _Dim[2*(1-RM)] = _dim[2*(1-RM)]*_Dim[1];
    }
    void _set_dimensions(size_t* d_) {
        _dim[0]        = d_[0];
        _dim[1]        = d_[1];
        _dim[2]        = d_[2];
        _Dim[2*RM]     = _dim[2*RM];
        _Dim[1]        = _dim[1]*_Dim[2*RM];
        _Dim[2*(1-RM)] = _dim[2*(1-RM)]*_Dim[1];
    }
public:
    Tensor(): _val(NULL) {}
    Tensor(size_t d1_, size_t d2_, size_t d3_) : _val(NULL) {
        _dim[0]        = d1_;
        _dim[1]        = d2_;
        _dim[2]        = d3_;
        _Dim[2*RM]     = _dim[2*RM];
        _Dim[1]        = _dim[1]*_Dim[2*RM];
        _Dim[2*(1-RM)] = _dim[2*(1-RM)]*_Dim[1];
    }
    elementType& operator[] (size_t i) {
        XC_CHECK_INDEX_ERROR(i, _Dim[2*(1-RM)]);
        return _val[i-index];
    }
    const elementType& operator[] (size_t i) const {
        XC_CHECK_INDEX_ERROR(i, _Dim[2*(1-RM)]);
        return _val[i-index];
    }
    elementType& operator() (
        size_t i1, size_t i2, size_t i3)
    {
        XC_CHECK_INDEX_ERROR(i1, _dim[0]);
        XC_CHECK_INDEX_ERROR(i2, _dim[1]);
        XC_CHECK_INDEX_ERROR(i3, _dim[2]);
        size_t i[3] = {i1-index, i2-index, i3-index};
        return _val[i[2*RM] + i[1]*_Dim[2*RM] + i[2*(1-RM)]*_Dim[1]];
    }
    const elementType& operator() (
        size_t i1, size_t i2, size_t i3) const
    {
        XC_CHECK_INDEX_ERROR(i1, _dim[0]);
        XC_CHECK_INDEX_ERROR(i2, _dim[1]);
        XC_CHECK_INDEX_ERROR(i3, _dim[2]);
        size_t i[3] = {i1-index, i2-index, i3-index};
        return _val[i[2*RM] + i[1]*_Dim[2*RM] + i[2*(1-RM)]*_Dim[1]];
    }
    elementType& operator() (size_t *i) {
        XC_CHECK_INDEX_ERROR(i[0], _dim[0]);
        XC_CHECK_INDEX_ERROR(i[1], _dim[1]);
        XC_CHECK_INDEX_ERROR(i[2], _dim[2]);
        return _val[(i[2*RM]-index) +
                    (i[1]-index)*_Dim[2*RM] +
                    (i[2*(1-RM)]-index)*_Dim[1]];
    }
    const elementType& operator() (size_t *i) const {
        XC_CHECK_INDEX_ERROR(i[0], _dim[0]);
        XC_CHECK_INDEX_ERROR(i[1], _dim[1]);
        XC_CHECK_INDEX_ERROR(i[2], _dim[2]);
        return _val[(i[2*RM]-index) +
                    (i[1]-index)*_Dim[2*RM] +
                    (i[2*(1-RM)]-index)*_Dim[1]];
    }
    size_t ndims() const {
        return 3;
    }
    const size_t& dim(size_t i) const {
        XC_CHECK_INDEX_ERROR(i, ndims());
        return _dim[i-index];
    }
    const size_t& size(size_t i) const {
        XC_CHECK_INDEX_ERROR(i, ndims());
        return _Dim[i-index];
    }
    elementType* data() const {
        return _val;
    }
    void display(std::ostream& out_) const {
        size_t k[3-2];
        if (RM == 0) {
            excentury::print_matrix_cm<3, elementType, index, RM>(
                out_, _val, _dim, _Dim, 3-1, k);
        } else {
            excentury::print_matrix_rm<3, elementType, index, RM>(
                out_, _val, _dim, _Dim, 3-1, k);
        }
    }
    void dbg_info() const {
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
        fprintf(stderr, "Tensor information: \n\n");
        fprintf(stderr, "ClassName      : ");
            XC_PRINT_CLASS_NAME(*(static_cast<const
            AllocationType*>(this))); fprintf(stderr, "\n");
        fprintf(stderr, "ElementType    : ");
            XC_PRINT_CLASS_NAME(elementType); fprintf(stderr, "\n");
        fprintf(stderr, "Index          : %d based index\n", index);
        fprintf(stderr, "RM             : %d "
                        "(1 is for row-major order, "
                        "0 is for column-major order)\n", RM);
        fprintf(stderr, "NDim           : %d\n", 3);
        fprintf(stderr, "dim            : {%d, %d, %d}\n",
                _dim[0], _dim[1], _dim[2]);
        fprintf(stderr, "size           : {%d, %d, %d}\n\n",
                _Dim[0], _Dim[1], _Dim[2]);
        fprintf(stderr, "\nArray of Matrices Contents: \n\n");
        #define XC_TMP 3, AllocationType, elementType, index, RM
        XCDisplay<XC_TMP>::display(std::cerr, *this);
        #undef XC_TMP
        fprintf(stderr, "-------------------------------------------"
                        "-------------------------------------\n");
    }
};

#undef XC_CHECK_INDEX_ERROR
#undef XC_CHECK_IX_ERROR

// Only use DEF_XC_DISPLAY on objects that work with
// std::cout. Once you define how to print a Tensor or
// any other object you may use this definition to display
// a Tensor when debugging. This may (may not) be worth it.
DEF_XC_DISPLAY(char);
DEF_XC_DISPLAY(signed char);
DEF_XC_DISPLAY(unsigned char);
DEF_XC_DISPLAY(short int);
DEF_XC_DISPLAY(int);
DEF_XC_DISPLAY(long int);
DEF_XC_DISPLAY(unsigned short int);
DEF_XC_DISPLAY(unsigned int);
DEF_XC_DISPLAY(unsigned long int);
DEF_XC_DISPLAY(float);
DEF_XC_DISPLAY(double);

}

#endif

// MACROS TO DEFINE HOW TO DUMP TEMPLATED TENSORS
// Assumming that t is an object, see use of this macro
// in staticTensor.h. This is meant to be used for N >= 2
#define XC_DUMP_TEMPLATED_TENSOR_DIM_N \
    size_t ndims = t.ndims(); \
    unsigned char rm = RM; \
    XC_BYTE(rm); \
    XC_SIZE(ndims); \
    size_t size = t.size((ndims-1)*(1-RM)+index); \
    XC_ARRAY(&t.dim(index), ndims); \
    XC_ARRAY(t.data(), size)

// Array requires a special case since the function
// size does not take an argument.
#define XC_DUMP_TEMPLATED_TENSOR_DIM_1 \
    size_t ndims = t.ndims(); \
    unsigned char rm = RM; \
    XC_BYTE(rm); \
    XC_SIZE(ndims); \
    size_t size = t.size(); \
    XC_ARRAY(&size, ndims); \
    XC_ARRAY(t.data(), size)

#ifdef XC_TENSOR_DEBUG
#include "../debug.h"
#endif
