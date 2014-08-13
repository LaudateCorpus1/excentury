/** STEXTINTERFACE.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: November 24, 2012
% Last Modified: November 24, 2013
*/
 
#ifdef XC_STEXTINTERFACE_DEBUG
#define DEBUGOFF XC_STEXTINTERFACE_DEBUG
#include "../debugoff.h"
#endif 

namespace excentury {

template<mode m>
class STextInterface: public Communicator< STextInterface<m> > {
public:
    STextInterface(): Communicator< STextInterface<m> >() {
        excentury::error("ERROR> STextInterface: mode not supported.");
    }
};

#define XC_COM_DM Communicator< STextInterface<dump_mode> >
template<>
class STextInterface<dump_mode>: public XC_COM_DM {
public:
    std::ostringstream oss;
    STextInterface(): XC_COM_DM(*this) {}
    void open(const char* fn) {
        trace("STextInterface<dump>::open()\n");
        if (!empty()) close();
        oss.clear();
        oss.str("");
    }
    void close() {
        trace("STextInterface<dump>::close()\n");
        XC_COM_DM::close();
    }
    std::string str() {
        return oss.str();
    }
    template<class T>
    void info(T& object_) {
        trace("  STextInterface<dump>::info:");
        oss << type(object_) << " ";
        switch (type(object_)) {
            case 'C': case 'I': case 'N': case 'R':
                trace(" %c %zu\n", type(object_), sizeof(object_));
                oss << sizeof(object_) << " "; break;
            case 'S':
                trace(" %c %s\n", type(object_), type_name(object_));
                oss << type_name(object_) << " "; break;
            default:
                char msg[500];
                sprintf(msg, "STextInterface<dump>::info: overload not found\n"
                        "    info overload not found for object of type '%c'", 
                        type(object_));
                excentury::error(msg);
        }
    }
    template<class T>
    void data(T& object_) {
        char msg[500];
        sprintf(msg, "STextInterface<dump>::data: overload not found\n"
                "    data overload not found for object '%s' of type '%c'", 
                type_name(object_), type(object_));
        excentury::error(msg);
    }
    template<class T>
    void data(T* object_, size_t total_) {
        trace("  STextInterface<dump>::data dumping %zd items\n", total_);
        for (size_t i=0; i < total_; ++i) {
            excentury::data(*this, object_[i], "");
        }
    }

    void data(const char& x) {oss << x << " ";}
    void data(const signed char& x) {oss << static_cast<signed>(x) << " ";}
    void data(const unsigned char& x) {oss << static_cast<unsigned>(x) << " ";}
    void data(const short int& x) {oss << x << " ";}
    void data(const int& x) {oss << x << " ";}
    void data(const long int& x) {oss << x << " ";}
    void data(const unsigned short int& x) {oss << x << " ";}
    void data(const unsigned int& x) {oss << x << " ";}
    void data(const unsigned long int& x) {oss << x << " ";}
    void data(const float& x) {oss << x << " ";}
    void data(const double& x) {oss << x << " ";}
    void data(const char* x, size_t total) {
        for (size_t i=0; i < total; ++i) oss << x[i];
        oss << " ";
    }

    void data(char& x) {oss << x << " ";}
    void data(signed char& x) {oss << static_cast<signed>(x) << " ";}
    void data(unsigned char& x) {oss << static_cast<unsigned>(x) << " ";}
    void data(short int& x) {oss << x << " ";}
    void data(int& x) {oss << x << " ";}
    void data(long int& x) {oss << x << " ";}
    void data(unsigned short int& x) {oss << x << " ";}
    void data(unsigned int& x) {oss << x << " ";}
    void data(unsigned long int& x) {oss << x << " ";}
    void data(float& x) {oss << x << " ";}
    void data(double& x) {oss << x << " ";}
    void data(char* x, size_t total) {
        for (size_t i=0; i < total; ++i) oss << x[i];
        oss << " ";
    }

    void transmit_type(char t) {
        trace(" STextInterface<dump>::transmit_type(%c)\n", t);
        oss << t << " ";
    }
    void transmit_byte(const unsigned char& b) {
        trace(" STextInterface<dump>::transmit_byte(%hhu)\n", b);
        oss << static_cast<unsigned>(b) << " ";
    }
    void transmit_number(size_t& num) {
        trace(" STextInterface<dump>::transmit_number(%lu)\n", num);
        oss << num << " ";
    }
    void transmit_string(std::string str) {
        trace(" STextInterface<dump>::transmit_string(%s)\n",
              str.c_str());
        oss << str << " ";
    }
    void transmit_num_objects() {
        trace(" STextInterface<dump>::transmit_num_objects(%lu)\n",
              object.size());
        oss << object.size() << "\n";
    }
    void transmit_num_samples() {
        trace(" STextInterface<dump>::transmit_num_samples(%lu)\n",
              sample.size());
        if (sample.size() > 0)
            oss << sample.size() << "\n";
        else
            oss << sample.size() << "\n";
    }
    void end_transmission() {
        trace(" STextInterface<dump>::end_transmission()\n");
        oss << "\n";
    }
};
#undef XC_COM_DM

#define XC_COM_LM Communicator< STextInterface<load_mode> >
template<>
class STextInterface<load_mode>: public XC_COM_LM {
public:
    std::istringstream iss;
    std::string tmp_str;
    size_t tmp_size;

    STextInterface(): XC_COM_LM(*this) {}
    STextInterface(const char* s): XC_COM_LM(*this), iss(s) {
        open(s);
    }
    STextInterface(const char* s, size_t l): XC_COM_LM(*this) {
        open(s, l);
    }
    void open(const char* s) {
        trace("STextInterface<load>::open(s)\n");
        if (!empty()) close();
        iss.clear();
        iss.str(s);
    }
    void open(const char* s, size_t l) {
        trace("STextInterface<load>.open(s, l)\n");
        if (!empty()) close();
        iss.clear();
        iss.str(s);
        //iss.rdbuf()->pubsetbuf((char*)s, l);
    }
    void close() {
        trace("STextInterface<load>::close()\n");
        if (!empty()) {
            XC_COM_LM::close();
        }
    }
    std::string str() {
        return iss.str();
    }
    template<class T>
    void info(T& object_) {
        trace("  STextInterface<load>::info:");
        iss >> tmp_str;
        if (tmp_str[0] != type(object_)) {
            char msg[500];
            sprintf(msg, "STextInterface<load>::info: type mismatch\n"
                    "    read '%s', expected '%c'", 
                    tmp_str.c_str(), type(object_));
            excentury::error(msg);
        }
        switch (type(object_)) {
            case 'C': case 'I': case 'N': case 'R':
                iss >> tmp_size;
                trace(" %c %zu\n", tmp_str[0], tmp_size);
                break;
            case 'S':
                iss >> tmp_str;
                if (strcmp(tmp_str.c_str(), type_name(object_)) != 0) {
                    char msg[500];
                    sprintf(msg, "STextInterface<load>::info: invalid type\n"
                            "    read '%s', expected '%s'", 
                            tmp_str.c_str(), type_name(object_));
                    excentury::error(msg);
                }
                trace(" %c %s\n", tmp_str[0], tmp_str.c_str());
                break;
            default:
                char msg[500];
                sprintf(msg, "STextInterface<load>::info: overload not found\n"
                        "    info overload not found for object of type '%c'", 
                        type(object_));
                excentury::error(msg);
        }
    }
    template<class T>
    void data(T& object_) {
        char msg[500];
        sprintf(msg, "STextInterface<load>::data: overload not found\n"
                "    data overload not found for object '%s' of type '%c'", 
                type_name(object_), type(object_));
        excentury::error(msg);
    }
    template<class T>
    void data(T* object_, size_t total_) {
        trace("  STextInterface<load>::data dumping %zd items\n", total_);
        for (size_t i=0; i < total_; ++i) {
            excentury::data(*this, object_[i], "");
        }
    }

    void data(char& x) {
        iss.get(); 
        x = iss.get();
    }
    void data(signed char& x) {
        int tmp_byte;
        iss >> tmp_byte;
        x = tmp_byte;
    }
    void data(unsigned char& x) {
        int tmp_byte;
        iss >> tmp_byte;
        x = tmp_byte;
    }
    void data(short int& x) {iss >> x;}
    void data(int& x) {iss >> x;}
    void data(long int& x) {iss >> x;}
    void data(unsigned short int& x) {iss >> x;}
    void data(unsigned int& x) {iss >> x;}
    void data(unsigned long int& x) {iss >> x;}
    void data(float& x) {iss >> x;}
    void data(double& x) {iss >> x;}
    void data(char* x, size_t total) {
        iss.get();
        for (size_t i=0; i < total; ++i) x[i] = iss.get();
        iss.get();
    }

    void transmit_type(char t) {
        iss >> t;
        trace(" STextInterface<load>::transmit_type(%c)\n", t);
    }
    void transmit_byte(unsigned char& b) {
        int tmp_byte;
        iss >> tmp_byte;
        b = tmp_byte;
        trace(" STextInterface<load>::transmit_byte(%hhu)\n", b);
    }
    void transmit_number(size_t& num) {
        iss >> num;
        trace(" STextInterface<load>::transmit_number(%lu)\n", num);
    }
    void transmit_string(std::string str) {
        iss >> str;
        trace(" STextInterface<load>::transmit_string(%s)\n", tmp_str.c_str());
    }
    void transmit_num_objects() {
        iss >> tmp_size;
        trace(" STextInterface<load>::transmit_num_objects(%lu)\n",
              tmp_size);
    }
    void transmit_num_samples() {
        iss >> tmp_size;
        trace(" STextInterface<load>::transmit_num_samples(%lu)\n",
              tmp_size);
    }
    void end_transmission() {}
};
#undef XC_COM_LM

}

#ifdef XC_STEXTINTERFACE_DEBUG
#include "../debug.h"
#endif
