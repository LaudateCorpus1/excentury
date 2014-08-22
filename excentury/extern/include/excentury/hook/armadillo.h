/** HOOK/ARMADILLO.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: BSD License
% Aug 22, 2014

This file defines how to adapt the armadillo objects to excentury. It
will only be included if the program is using the armadillo library:

http://arma.sourceforge.net/

NOTE: Armadillo must be included before excentury.

*/

#ifdef ARMA_INCLUDES

namespace excentury {

// Mat<type>
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
        sprintf(msg, "Armadillo Mat::load('%s'):\n"
                "    dimension mismatch, needs dim = 2", varname);
        excentury::error(msg);
    }
    size_t* dim = new size_t[ndims];
    XC_ARRAY(dim, ndims);
    m.set_size(dim[0], dim[1]);
    elementType* mem = const_cast<elementType*>(m.mem);
    XC_ARRAY(mem, m.n_elem);
    delete [] dim;
}

// Col<type>
XC_DUMP_TEMPLATED_TENSOR(class elementType, arma::Col<elementType>, m, m.mem[0]) {
    size_t ndims = 1;
    unsigned char rm = 0;
    XC_BYTE(rm);
    XC_SIZE(ndims);
    size_t size = m.n_elem;
    size_t dim[1] = {m.n_rows};
    XC_ARRAY(dim, ndims);
    XC_ARRAY(m.mem, size);
}
XC_LOAD_TEMPLATED_TENSOR(class elementType, arma::Col<elementType>, m) {
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
    if (ndims != 1) {
        char msg[500];
        sprintf(msg, "Armadillo Mat::load('%s'):\n"
                "    dimension mismatch, needs dim = 1", varname);
        excentury::error(msg);
    }
    size_t* dim = new size_t[ndims];
    XC_ARRAY(dim, ndims);
    m.set_size(dim[0]);
    elementType* mem = const_cast<elementType*>(m.mem);
    XC_ARRAY(mem, m.n_elem);
    delete [] dim;
}

// Row<type>
XC_DUMP_TEMPLATED_TENSOR(class elementType, arma::Row<elementType>, m, m.mem[0]) {
    size_t ndims = 1;
    unsigned char rm = 0;
    XC_BYTE(rm);
    XC_SIZE(ndims);
    size_t size = m.n_elem;
    size_t dim[1] = {m.n_cols};
    XC_ARRAY(dim, ndims);
    XC_ARRAY(m.mem, size);
}
XC_LOAD_TEMPLATED_TENSOR(class elementType, arma::Row<elementType>, m) {
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
    if (ndims != 1) {
        char msg[500];
        sprintf(msg, "Armadillo Mat::load('%s'):\n"
                "    dimension mismatch, needs dim = 1", varname);
        excentury::error(msg);
    }
    size_t* dim = new size_t[ndims];
    XC_ARRAY(dim, ndims);
    m.set_size(dim[0]);
    elementType* mem = const_cast<elementType*>(m.mem);
    XC_ARRAY(mem, m.n_elem);
    delete [] dim;
}

// Cube<type>
XC_DUMP_TEMPLATED_TENSOR(class elementType, arma::Cube<elementType>, m, m.mem[0]) {
    size_t ndims = 3;
    unsigned char rm = 0;
    XC_BYTE(rm);
    XC_SIZE(ndims);
    size_t size = m.n_elem;
    size_t dim[3] = {m.n_rows, m.n_cols, m.n_slices};
    XC_ARRAY(dim, ndims);
    XC_ARRAY(m.mem, size);
}
XC_LOAD_TEMPLATED_TENSOR(class elementType, arma::Cube<elementType>, m) {
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
    if (ndims != 3) {
        char msg[500];
        sprintf(msg, "Armadillo Mat::load('%s'):\n"
                "    dimension mismatch, needs dim = 3", varname);
        excentury::error(msg);
    }
    size_t* dim = new size_t[ndims];
    XC_ARRAY(dim, ndims);
    m.set_size(dim[0], dim[1], dim[2]);
    elementType* mem = const_cast<elementType*>(m.mem);
    XC_ARRAY(mem, m.n_elem);
    delete [] dim;
}
}

#endif
