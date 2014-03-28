/** MLINTERFACE.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: January 02, 2014
*/

#ifdef _MATHLINK_H

#ifdef XC_MLINTERFACE_DEBUG
#define DEBUGOFF XC_MLINTERFACE_DEBUG
#include "../debugoff.h"
#endif 

namespace excentury {
    
template<mode m>
class MLInterface: public communicator< MLInterface<m> > {
public:
    MLInterface(): communicator< MLInterface<m> >() {
        printf("ERROR> MLInterface does not support this mode.\n");
        exit(1);
    }
};

#define XC_COM_DM communicator< MLInterface<dump_mode> >
template<>
class MLInterface<dump_mode>: public XC_COM_DM {
public:
    MLInterface() : XC_COM_DM(*this) {}
    void close() {
        trace("MLInterface<dump>.close()\n");
        XC_COM_DM::close();
    }
    template <class T>
    static void info(MLInterface& interface, T& x) {
        trace(" MLInterface<dump>::info:");
        /*
        fprintf(interface.fp, "%c ", type(x));
        switch (type(x)) {
            case 'C': case 'B': case 'I':
            case 'c': case 'N': case 'R':
                trace(" %c %ld\n", type(x), sizeof(x));
                fprintf(interface.fp, "%ld ", sizeof(x)); break;
            case 'S':
                trace(" %c %s\n", type(x), type_name(x));
                fprintf(interface.fp, "%s ", type_name(x)); break;
            default:
                fprintf(stderr,
                        "ERROR: MLInterface::info<dump_mode> -> "
                        "info overload not found for object of type "
                        "\"%c\".\n", type(x)); 
                exit(1);
        }
        */
    }
    template <class T>
    static void data(MLInterface& interface, T& x) {
        fprintf(stderr, 
                "ERROR: MLInterface<dump>::data -> "
                "data overload not found for \"%c %s\".\n", 
                type(x), type_name(x)); 
        exit(1);
    }
    template <class T>
    static void data(MLInterface& interface, T* x, size_t total) {
        trace(" MLInterface<dump>::data: dumping %zd items\n", 
              total);
        for (int i=0; i < total; ++i) {
            excentury::data(interface, x[i], "null");
        }
    }
    void data_str(char* x, size_t total) {
        MLPutString(stdlink, (const char*)x);
        /*
        for (int i=0; i < total; ++i) {
            fprintf(fp, "%c", x[i]);
        }*/
        //fprintf(fp, " ");
    }
    void data_str(const char* x, size_t total) {
        MLPutString(stdlink, x);
        /*
        for (int i=0; i < total; ++i) {
            fprintf(fp, "%c", x[i]);
        }
        fprintf(fp, " ");*/
    }
    void _trans_type(char t) {
        trace(" MLInterface<dump>::_trans_type(%c)\n", t);
        //fprintf(fp, "%c ", t);
    }
    void _trans_byte(XC_BYTE& b) {
        trace(" MLInterface<dump>::_trans_byte(%hhu)\n", b);
        //fprintf(fp, "%hhu ", b);
    }
    void _trans_num(size_t& num) {
        trace(" MLInterface<dump>::_trans_num(%lu)\n", num);
        //MLPutSize(stdlink, num);
    }
    void _trans_varname(std::string& varname) {
        trace(" MLInterface<dump>::_trans_varname(%s)\n", 
              varname.c_str());
        //fprintf(fp, "%s ", varname.c_str());
    }
    void _trans_name(std::string str) {
        trace(" MLInterface<dump>::_trans_name(%s)\n", 
              str.c_str());
        //fprintf(fp, "%s ", str.c_str());
    }
    void _trans_num_objects() {
        trace(" MLInterface<dump>::_trans_num_objects(%lu)\n", 
              obj.size());
        //fprintf(fp, "%lu\n", obj.size());
    }
    void _trans_num_classes() {
        trace(" MLInterface<dump>::_trans_num_classes(%lu)\n", 
              cls.size());
        //MLPutSize(stdlink, cls.size());
    }
    void _trans_close() {
        trace(" MLInterface<dump>::_trans_close()\n");
        //fprintf(fp, "\n");
    }
};
#undef XC_COM_DM

#define FUNC_DEF(obj) template<> inline \
    void MLInterface<dump_mode>::data(MLInterface& interface, obj)

FUNC_DEF(char& x) { 
    MLPutNext(stdlink, MLTKSTR);
    MLPutSize(stdlink, 1);
    MLPutData(stdlink, &x, 1); 
}
FUNC_DEF(signed char& x) { MLPutInteger(stdlink, x); }
FUNC_DEF(unsigned char& x) { MLPutInteger(stdlink, x); }

FUNC_DEF(short int& x) { MLPutInteger16(stdlink, x); }
FUNC_DEF(int& x) { MLPutInteger32(stdlink, x); }
FUNC_DEF(long int& x) { MLPutInteger64(stdlink, x); }

FUNC_DEF(unsigned short int& x) { MLPutInteger16(stdlink, x); }
FUNC_DEF(unsigned int& x) { MLPutInteger32(stdlink, x); }
FUNC_DEF(unsigned long int& x) { MLPutInteger64(stdlink, x); }

FUNC_DEF(float& x) { MLPutFloat(stdlink, x); }
FUNC_DEF(double& x) { MLPutDouble(stdlink, x); }

FUNC_DEF(const char& x) {
    MLPutNext(stdlink, MLTKSTR);
    MLPutSize(stdlink, 1);
    MLPutData(stdlink, &x, 1);
}
FUNC_DEF(const signed char& x) { MLPutInteger(stdlink, x); }
FUNC_DEF(const unsigned char& x) { MLPutInteger(stdlink, x); }

FUNC_DEF(const short int& x) { MLPutInteger16(stdlink, x); }
FUNC_DEF(const int& x) { MLPutInteger32(stdlink, x); }
FUNC_DEF(const long int& x) { MLPutInteger64(stdlink, x); }

FUNC_DEF(const unsigned short int& x) { MLPutInteger16(stdlink, x); }
FUNC_DEF(const unsigned int& x) { MLPutInteger32(stdlink, x); }
FUNC_DEF(const unsigned long int& x) { MLPutInteger64(stdlink, x); }

FUNC_DEF(const float& x) { MLPutFloat(stdlink, x); }
FUNC_DEF(const double& x) { MLPutDouble(stdlink, x); }

#undef FUNC_DEF


#define XC_COM_LM communicator< MLInterface<load_mode> >
template<>
class MLInterface<load_mode>: public XC_COM_LM {
public:
    char tmp_str[101];
    size_t tmp_size;
    
    MLInterface(): XC_COM_LM(*this) {}
    void close() {
        XC_COM_LM::close();
    }
    template <class T>
    static void info(MLInterface& interface, T& x) {
        /*
        fscanf(interface.fp, "%s ", interface.tmp_str);
        exitif(interface.tmp_str[0] != type(x), NULL, 
               "Type mismatch: Interface read '%s' "
               "while trying to load '%c'\n", 
               interface.tmp_str, type(x));
        trace(" MLInterface<load>::info: %c", interface.tmp_str[0]);
        switch (type(x)) {
            case 'C': case 'B': case 'I':
            case 'c': case 'N': case 'R':
                fscanf(interface.fp, "%lu ", &interface.tmp_size); 
                trace(" %lu\n", sizeof(x));
                break;
            case 'S':
                fscanf(interface.fp, "%s ", interface.tmp_str);
                exitif(strcmp(interface.tmp_str, type_name(x)) != 0, 
                       NULL, "Invalid type: Interface read '%s' "
                       "while trying to load '%s'\n", 
                       interface.tmp_str, type_name(x));
                trace(" %s\n", type_name(x));
                break;
            default:
                fprintf(stderr, "ERROR: MLInterface<load_mode>::info "
                       "-> info overload not found for object of "
                       "type \"%c\".\n", type(x)); 
                exit(1);
        }
        */
    }
    template <class T>
    static void data(MLInterface& interface, T& x) {
        fprintf(stderr, "ERROR: MLInterface::data -> "
                "data overload not found for \"%c %s\".\n", 
                type(x), type_name(x)); 
        exit(1);
    }
    template <class T>
    static void data(MLInterface& interface, T* x, size_t total) {
        trace(" MLInterface<load>::data: reading %zd items\n", total);
        for (int i=0; i < total; ++i) {
            excentury::data(interface, x[i], "null");
        }
    }
    void data_str(char* x, size_t total) {
        /*
        for (int i=0; i < total; ++i) {
            x[i] = fgetc(fp);
        }
        fgetc(fp);
        */
    }
    
    void _trans_type(char t) {
        /*
        fscanf(fp, "%c ", &t);
        trace(" MLInterface<load>::_trans_type: %c\n", t);
        */
    }
    void _trans_num(size_t& num) {
        /*
        fscanf(fp, "%lu ", &num);
        trace(" MLInterface<load>::_trans_num: %lu\n", num);
        */
    }
    void _trans_byte(XC_BYTE& b) {
        /*
        fscanf(fp, "%hhu ", &b);
        trace(" MLInterface<load>::_trans_byte: %hhu\n", b);
        */
    }
    void _trans_varname(std::string& varname){
        /*
        fscanf(fp, "%s ", tmp_str);
        varname = tmp_str;
        trace(" MLInterface<load>::_trans_varname: %s\n", tmp_str);
        */
    }
    void _trans_name(std::string str) {
        /*
        fscanf(fp, "%s ", tmp_str);
        trace(" MLInterface<load>::_trans_name: %s\n", tmp_str);
        */
    }
    void _trans_num_objects() {
        /*
        fscanf(fp, "%zu", &interface.tmp_size);
        trace(" MLInterface<load>::_trans_num_objects: %zu\n", 
              interface.tmp_size);*/
    }
    void _trans_num_classes() {
        /*
        fscanf(fp, "%zu", &interface.tmp_size);
        trace(" MLInterface<load>::_trans_num_classes: %zu\n", 
              interface.tmp_size);
        exitif(interface.tmp_size != this->cls.size(), NULL, 
               "Your instructions were not able to pick up all \n"
               "the required objects. A common mistake happens when \n"
               "trying to load tensors of non standard objects. When \n"
               "this is the case use the form "
               "interface.load(var, sample) instead.\n");*/
    }
    void _trans_close() {}
};
#undef XC_COM_LM

#define FUNC_DEF(obj) template<> inline void \
    MLInterface<load_mode>::data(MLInterface& interface, obj)

FUNC_DEF(char& x) {
}
FUNC_DEF(signed char& x) { MLGetInteger(stdlink, (int*)&x); }
FUNC_DEF(unsigned char& x) { MLGetInteger(stdlink, (int*)&x); }

FUNC_DEF(short int& x) { MLGetInteger16(stdlink, &x); }
FUNC_DEF(int& x) { MLGetInteger32(stdlink, &x); }
FUNC_DEF(long int& x) { MLGetInteger64(stdlink, &x); }

FUNC_DEF(unsigned short int& x) { MLGetInteger16(stdlink, (short int*)&x); }
FUNC_DEF(unsigned int& x) { MLGetInteger32(stdlink, (int*)&x); }
FUNC_DEF(unsigned long int& x) { MLGetInteger64(stdlink, (long int*)&x); }

FUNC_DEF(float& x) { MLGetReal32(stdlink, &x); }
FUNC_DEF(double& x) { MLGetReal64(stdlink, &x); }

#undef FUNC_DEF

}

#ifdef XC_MLINTERFACE_DEBUG
#include "../debug.h"
#endif

#endif
