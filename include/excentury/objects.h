namespace excentury {

// Adapting std::string to excentury
XC_DUMP_WORDS(std::string, s) {
    size_t size = s.size();
    XC_SIZE(size);
    XC_ARRAY(s.c_str(), size);
}
XC_LOAD_WORDS(std::string, s) {
    char* ptr = NULL;
    size_t size;
    XC_SIZE(size);
    ptr = new char[size];
    XC_ARRAY(ptr, size);
    std::string tmp(ptr, size);
    s = tmp; delete [] ptr;
}

// Adapting std::vector to excentury
XC_DUMP_TEMPLATED_TENSOR(class T, std::vector<T>, v, v[0]) {
    size_t dim = 1;
    size_t size = v.size();
    unsigned char row_major = 0;
    XC_BYTE(row_major);
    XC_SIZE(dim);
    XC_ARRAY(&size, dim);
    XC_ARRAY(v.data(), size);
}
XC_LOAD_TEMPLATED_TENSOR(class T, std::vector<T>, v) {
    size_t dim;
    size_t size;
    unsigned char row_major;
    XC_BYTE(row_major);
    XC_SIZE(dim);
    XC_ARRAY(&size, dim);
    v.resize(size);
    XC_ARRAY(v.data(), size);
}

}
