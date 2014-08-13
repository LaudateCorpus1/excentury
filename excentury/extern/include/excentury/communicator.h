/** COMMUNICATOR.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% NOTE: See http://stackoverflow.com/a/12607293/788553

*/

#ifdef XC_COMMUNICATOR_DEBUG
#define DEBUGOFF XC_COMMUNICATOR_DEBUG
#include "debugoff.h"
#endif

namespace excentury {

enum mode {dump_mode, load_mode};

//--------------------------------------------------------------------
// BaseType
//--------------------------------------------------------------------
class BaseType {
public:
    std::string name;
    BaseType(std::string name_): name(name_) {}
    virtual ~BaseType() {}
    virtual void communicate() = 0;
    virtual void append_definition() = 0;
    virtual void transmit_definition() = 0;
    virtual void* pointer() = 0;
    virtual char get_type() = 0;
    virtual int size() = 0;
    virtual std::string get_type_name() = 0;
};

//--------------------------------------------------------------------
// Communicator
//--------------------------------------------------------------------
template<class T, class InterfaceType> class DataType;
#define XC_DATATYPE(name) \
    (BaseType*)(new DataType<T, InterfaceType>(name, object_, interface))
template<class InterfaceType>
class Communicator {
public:
    InterfaceType& interface;
    std::vector<BaseType*> object;
    std::vector<BaseType*> sample;

    Communicator(InterfaceType& interface_): interface(interface_) {}
    ~Communicator() {
        trace("~Communicator()\n");
        clear();
    }
    template<class T>
    void store_sample(T& object_) {
        trace("Communicator::store_sample('%s')\n", type_name(object_));
        if (type(object_) == 'S') {
            bool in_sample = false;
            for (size_t i=0; i < sample.size(); ++i) {
                if (sample[i]->get_type_name() == type_name(object_)) {
                    in_sample = true;
                    break;
                }
            }
            if (!in_sample) {
                trace("  -->push_back('%s')\n", type_name(object_));
                sample.push_back(XC_DATATYPE(""));
                sample.back()->append_definition();
            }
        }
    }
    template<class T>
    void dump(T& object_, const char* name_) {
        trace("Communicator::dump('%s')\n", name_);
        if (type(object_) == 'T') {
            char msg[500];
            sprintf(msg, "Communicator::dump('%s'): \n"
                    "    A sample item needs to be provided when "
                    "dumping a tensor. ", name_);
            excentury::error(msg);
        }
        object.push_back(XC_DATATYPE(name_));
        store_sample(object_);
    }
    template<class T, class M>
    void dump(T& object_, const char* name_, M& sample_) {
        trace("Communicator::dump('%s', '%s')\n",
              name_, type_name(sample_));
        object.push_back(XC_DATATYPE(name_));
        store_sample(sample_);
    }
    template<class T>
    void load(T& object_) {
        trace("Communicator::load('%s')\n", type_name(object_));
        if (type(object_) == 'T') {
            char msg[500];
            sprintf(msg, "Communicator::load: \n"
                    "    A sample item needs to be provided when "
                    "loading a tensor. ");
            excentury::error(msg);
        }
        object.push_back(XC_DATATYPE(""));
        store_sample(object_);
    }
    template<class T, class M>
    void load(T& object_, M& sample_) {
        trace("Communicator::load('%s', '%s')\n",
              type_name(object_), type_name(sample_));
        object.push_back(XC_DATATYPE(""));
        store_sample(sample_);
    }
    void clear() {
        trace("Communicator::clear()\n");
        for (size_t i = 0; i < object.size(); ++i) delete object[i];
        for (size_t i = 0; i < sample.size(); ++i) delete sample[i];
        object.clear();
        sample.clear();
    }
    bool empty() {
        return object.empty();
    }
    virtual void open() {}
    virtual void close() {
        interface.transmit_num_samples();
        for (size_t i=0; i < sample.size(); ++i) {
            sample[i]->transmit_definition();
        }
        interface.transmit_num_objects();
        for (size_t i=0; i < object.size(); ++i) {
            object[i]->communicate();
        }
        clear();
        trace("Communicator::close()\n");
    }
};
#undef XC_DATATYPE

}

#ifdef XC_COMMUNICATOR_DEBUG
#include "debug.h"
#endif
