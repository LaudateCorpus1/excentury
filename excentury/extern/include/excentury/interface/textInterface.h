/** TEXTINTERFACE.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/
% Date Created: July 05, 2012
% Last Modified: November 26, 2013
*/

#ifdef XC_TEXTINTERFACE_DEBUG
#define DEBUGOFF XC_TEXTINTERFACE_DEBUG
#include "../debugoff.h"
#endif

namespace excentury {

template<mode m>
class TextInterface: public Communicator< TextInterface<m> > {
public:
    TextInterface(): Communicator< TextInterface<m> >() {
        excentury::error("ERROR> TextInterface: mode not supported.");
    }
};

#define XC_COM_DM Communicator< TextInterface<dump_mode> >
template<>
class TextInterface<dump_mode>: public XC_COM_DM {
public:
    FILE* fp;
    bool stdstream;
    TextInterface(): XC_COM_DM(*this), fp(NULL), stdstream(false) {}
    TextInterface(const char* fn): XC_COM_DM(*this), fp(NULL) {
        open(fn);
    }
    TextInterface(FILE* fn): XC_COM_DM(*this), fp(NULL) {
        open(fn);
    }
    void open(const char* fn) {
        trace("TextInterface<dump>::open('%s')\n", fn);
        close();
        fp = fopen(fn, "w");
        stdstream = false;
    }
    void open(FILE* fn) {
        trace("TextInterface<dump>::open(FILE*)\n");
        close();
        fp = fn;
        stdstream = true;
    }
    void close() {
        trace("TextInterface<dump>::close()\n");
        if (fp != NULL) {
            XC_COM_DM::close();
            if (!stdstream) {
                fclose(fp);
            }
            fp = NULL;
        }
    }
    template<class T>
    void info(T& object_) {
        trace("  TextInterface<dump>::info:");
        fprintf(fp, "%c ", type(object_));
        switch (type(object_)) {
            case 'C': case 'I': case 'N': case 'R':
                trace(" %c %zu\n", type(object_), sizeof(object_));
                fprintf(fp, "%zu ", sizeof(object_)); break;
            case 'S':
                trace(" %c %s\n", type(object_), type_name(object_));
                fprintf(fp, "%s ", type_name(object_)); break;
            default:
                char msg[500];
                sprintf(msg, "TextInterface<dump>::info: overload not found\n"
                        "    info overload not found for object of type '%c'", 
                        type(object_));
                excentury::error(msg);
        }
    }
    template<class T>
    void data(T& object_) {
        char msg[500];
        sprintf(msg, "TextInterface<dump>::data: overload not found\n"
                "    data overload not found for object %s of type '%c'", 
                type_name(object_), type(object_));
        excentury::error(msg);
    }
    template<class T>
    void data(T* object_, size_t total_) {
        trace("  TextInterface<dump>::data dumping %zd items\n", total_);
        for (size_t i=0; i < total_; ++i) {
            excentury::data(*this, object_[i], "");
        }
    }

    void data(const char& x) {fprintf(fp, "%c ", x);}
    void data(const signed char& x) {fprintf(fp, "%hhu ", x);}
    void data(const unsigned char& x) {fprintf(fp, "%hhu ", x);}
    void data(const short int& x) {fprintf(fp, "%hd ", x);}
    void data(const int& x) {fprintf(fp, "%d ", x);}
    void data(const long int& x) {fprintf(fp, "%ld ", x);}
    void data(const unsigned short int& x) {fprintf(fp, "%hu ", x);}
    void data(const unsigned int& x) {fprintf(fp, "%u ", x);}
    void data(const unsigned long int& x) {fprintf(fp, "%lu ", x);}
    void data(const float& x) {fprintf(fp, "%f ", x);}
    void data(const double& x) {fprintf(fp, "%lf ", x);}
    void data(const char* x, size_t total) {
        for (size_t i=0; i < total; ++i) fprintf(fp, "%c", x[i]);
        fprintf(fp, " ");
    }

    void data(char& x) {fprintf(fp, "%c ", x);}
    void data(signed char& x) {fprintf(fp, "%hhu ", x);}
    void data(unsigned char& x) {fprintf(fp, "%hhu ", x);}
    void data(short int& x) {fprintf(fp, "%hd ", x);}
    void data(int& x) {fprintf(fp, "%d ", x);}
    void data(long int& x) {fprintf(fp, "%ld ", x);}
    void data(unsigned short int& x) {fprintf(fp, "%hu ", x);}
    void data(unsigned int& x) {fprintf(fp, "%u ", x);}
    void data(unsigned long int& x) {fprintf(fp, "%lu ", x);}
    void data(float& x) {fprintf(fp, "%f ", x);}
    void data(double& x) {fprintf(fp, "%lf ", x);}
    void data(char* x, size_t total) {
        for (size_t i=0; i < total; ++i) fprintf(fp, "%c", x[i]);
        fprintf(fp, " ");
    }

    void transmit_type(char t) {
        trace(" TextInterface<dump>::transmit_type(%c)\n", t);
        fprintf(fp, "%c ", t);
    }
    void transmit_byte(const unsigned char& b) {
        trace(" TextInterface<dump>::transmit_byte(%hhu)\n", b);
        fprintf(fp, "%hhu ", b);
    }
    void transmit_number(size_t& num) {
        trace(" TextInterface<dump>::transmit_number(%lu)\n", num);
        fprintf(fp, "%zu ", num);
    }
    void transmit_string(std::string str) {
        trace(" TextInterface<dump>::transmit_string(%s)\n",
              str.c_str());
        fprintf(fp, "%s ", str.c_str());
    }
    void transmit_num_objects() {
        trace(" TextInterface<dump>::transmit_num_objects(%lu)\n",
              object.size());
        fprintf(fp, "%zu\n", object.size());
    }
    void transmit_num_samples() {
        trace(" TextInterface<dump>::transmit_num_samples(%lu)\n",
              sample.size());
        if (sample.size() > 0)
            fprintf(fp, "%zu\n", sample.size());
        else
            fprintf(fp, "%zu ", sample.size());
    }
    void end_transmission() {
        trace(" TextInterface<dump>::end_transmission()\n");
        fprintf(fp, "\n");
    }
};
#undef XC_COM_DM

#define XC_COM_DM Communicator< TextInterface<load_mode> >
template<>
class TextInterface<load_mode>: public XC_COM_DM {
public:
    FILE* fp;
    char tmp_str[101];
    size_t tmp_size;

    TextInterface(): XC_COM_DM(*this), fp(NULL) {}
    TextInterface(const char* fn): XC_COM_DM(*this), fp(NULL) {
        open(fn);
    }
    void open(const char* fn) {
        trace("TextInterface<load>::open('%s')\n", fn);
        if (fp != NULL) close();
        fp = fopen(fn, "r");
        if (fp == NULL) {
            fprintf(stderr, "Unable to open '%s'\n", fn);
            exit(0);
        }
    }
    void close() {
        trace("TextInterface<load>::close()\n");
        if (fp != NULL) {
            XC_COM_DM::close();
            fclose(fp);
            fp = NULL;
        }
    }
    template<class T>
    void info(T& object_) {
        trace("  TextInterface<load>::info:");
        fscanf(fp, "%s ", tmp_str);
        if (tmp_str[0] != type(object_)) {
           char msg[500];
           sprintf(msg, "TextInterface<load>::info: type mismatch\n"
                   "    read '%s', expected '%c'", 
                   tmp_str, type(object_));
           excentury::error(msg);
        }
        switch(type(object_)) {
            case 'C': case 'I': case 'N': case 'R':
                fscanf(fp, "%zu ", &tmp_size);
                trace(" %c %zu\n", tmp_str[0], tmp_size);
                break;
            case 'S':
                fscanf(fp, "%s ", &tmp_str);
                if (strcmp(tmp_str, type_name(object_)) != 0) {
                    char msg[500];
                    sprintf(msg, "TextInterface<load>::info: invalid type\n"
                            "    read '%s', expected '%s'", 
                            tmp_str, type_name(object_));
                    excentury::error(msg);
                }
                break;
            default:
                char msg[500];
                sprintf(msg, "TextInterface<load>::info: overload not found\n"
                        "    info overload not found for object of type '%c'", 
                        type(object_));
                excentury::error(msg);
        }
    }
    template<class T>
    void data(T& object_) {
        char msg[500];
        sprintf(msg, "TextInterface<load>::data: overload not found\n"
                "    data overload not found for object %s of type '%c'", 
                type_name(object_), type(object_));
        excentury::error(msg);
    }
    template<class T>
    void data(T* object_, size_t total_) {
        trace("  TextInterface<load>::data dumping %zd items\n", total_);
        for (size_t i=0; i < total_; ++i) {
            excentury::data(*this, object_[i], "");
        }
    }

    void data(char& x) {x = fgetc(fp); fgetc(fp);}
    void data(signed char& x) {fscanf(fp, "%hhu ", &x);}
    void data(unsigned char& x) {fscanf(fp, "%hhu ", &x);}
    void data(short int& x) {fscanf(fp, "%hd ", &x);}
    void data(int& x) {fscanf(fp, "%d ", &x);}
    void data(long int& x) {fscanf(fp, "%ld ", &x);}
    void data(unsigned short int& x) {fscanf(fp, "%hu ", &x);}
    void data(unsigned int& x) {fscanf(fp, "%u ", &x);}
    void data(unsigned long int& x) {fscanf(fp, "%lu ", &x);}
    void data(float& x) {fscanf(fp, "%f ", &x);}
    void data(double& x) {fscanf(fp, "%lf ", &x);}
    void data(char* x, size_t total) {
        for (size_t i=0; i < total; ++i) x[i] = fgetc(fp);
        fgetc(fp);
    }

    void transmit_type(char t) {
        fscanf(fp, "%c ", &t);
        trace(" TextInterface<load>::transmit_type(%c)\n", t);
    }
    void transmit_byte(unsigned char& b) {
        fscanf(fp, "%hhu ", &b);
        trace(" TextInterface<load>::transmit_byte(%hhu)\n", b);
    }
    void transmit_number(size_t& num) {
        fscanf(fp, "%zu ", &num);
        trace(" TextInterface<load>::transmit_number(%lu)\n", num);
    }
    void transmit_string(std::string str) {
        fscanf(fp, "%s ", tmp_str);
        str = tmp_str;
        trace(" TextInterface<load>::transmit_string(%s)\n", tmp_str);
    }
    void transmit_num_objects() {
        fscanf(fp, "%zu\n", &tmp_size);
        trace(" TextInterface<load>::transmit_num_objects(%lu)\n",
              tmp_size);
    }
    void transmit_num_samples() {
        fscanf(fp, "%zu\n", &tmp_size);
        trace(" TextInterface<load>::transmit_num_samples(%lu)\n",
              tmp_size);
    }
    void end_transmission() {}
};
#undef XC_COM_DM

}

#ifdef XC_TEXTINTERFACE_DEBUG
#include "../debug.h"
#endif
