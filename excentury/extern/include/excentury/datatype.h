/** DATATYPE.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/

*/

#ifdef XC_DATATYPE_DEBUG
#define DEBUGOFF XC_DATATYPE_DEBUG
#include "debugoff.h"
#endif

namespace excentury {

template<class T, class InterfaceType>
class DataType : public BaseType {
private:
    T& object;
    InterfaceType& interface;
public:
    DataType(const char* name_, T& object_, InterfaceType& interface_):
        BaseType(name_), object(object_), interface(interface_)
    {}
    void communicate() {
        trace("DataType::communicate()\n");
        interface.transmit_string(name);
        info(interface, object);
        data(interface, object, name.c_str());
        interface.end_transmission();
    }
    void append_definition() {
        trace("DataType::append_definition()\n");
        append_sample(interface, object, name.c_str());
    }
    void transmit_definition() {
        trace("DataType::transmit_definition()\n");
        interface.transmit_string(get_type_name());
        info(interface, object, name.c_str());
        interface.end_transmission();
    }
    void* pointer() {return (void*)(&object);}
    char get_type() {return type(object);}
    int size() {return sizeof(object);}
    std::string get_type_name() {return type_name(object);}
};

}

#ifdef XC_DATATYPE_DEBUG
#include "debug.h"
#endif
