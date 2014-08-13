/** ERROR.H
% Author: Manuel Lopez <jmlopez.rod@gmail.com>
% License: http://creativecommons.org/licenses/by-sa/3.0/

RuntimeError
------------

- Defines an std::exception derived object and the function error to
  exit from the program gracefully depending on the type of language
  we are using.

*/

namespace excentury {

class RuntimeError: public std::exception {
public:
    std::string msg;
    RuntimeError(std::string msg_) {
        msg = "E" + std::string(msg_);
    }
    ~RuntimeError() throw () {}
    const char* c_str() const throw() {
        return msg.c_str();
    }
    size_t size() const throw() {
        return msg.size();
    }
};

void error(const char* msg_, int code=1) {
#if defined (XC_MATLAB)
    mexErrMsgTxt(msg_);
#elif defined (XC_PYTHON)
    throw RuntimeError(msg_);
#else
    fprintf(stderr, "FATAL ERROR: %s\n", msg_);
    exit(code);
#endif
}

}
