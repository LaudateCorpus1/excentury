/** TYPES.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/

type and type_name
------------------

- Provides functions to obtain the type of an object.

*/

namespace excentury {

#define XC_TYPE template<> inline char type
template<class> struct TypeAux {
    static inline char type() {return 'S';}
};
template<class T> inline char type(const T&) {return TypeAux<T>::type();}
template<class T> inline char type(T*) {return 'P';}
XC_TYPE(const char&) {return 'C';}           // 1 byte
XC_TYPE(const signed char&) {return 'I';}    // 1 byte: -128 to 127
XC_TYPE(const unsigned char&) {return 'N';}  // 1 byte: 0 to 255
XC_TYPE(const short int&) {return 'I';}  // 2 bytes
XC_TYPE(const int&) {return 'I';}        // 4 bytes
XC_TYPE(const long int&) {return 'I';}   // 8 bytes
XC_TYPE(const unsigned short int&) {return 'N';}  // 2 bytes
XC_TYPE(const unsigned int&) {return 'N';}        // 4 bytes
XC_TYPE(const unsigned long int&) {return 'N';}   // 8 bytes
XC_TYPE(const float&) {return 'R';}   // 4 bytes
XC_TYPE(const double&) {return 'R';}  // 8 bytes
#undef XC_TYPE

template<class T> inline const char* type_name(const T&) {
    return "";
}

}
