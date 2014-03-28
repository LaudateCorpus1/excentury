// File generated on Wed Jan 22, 2014 02:27:30 AM by xcpp.
#include <excentury/excentury.h>
#include <excentury/hook/cpp.h>
#include <objects.h>
// print_msg
void xc_help() {
    fprintf(stderr,
    "program: util-print_msg\n"
    "\ndescription:\n"
    "    Print a message to the standard error stream.\n"
    "\nparameters:\n"
    "    `msg`: the message to be printed.\n"
    "\n");
}
void xc_input() {
    xc_help();
    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    std::string msg; XC_DI_.dump(msg, "msg");
    XC_DI_.close();
}
int main(int argc, char** argv) {
    /*Print a message to the standard error stream.*/
    excentury::check_inputs(argc);
    excentury::print_help(argv, xc_help);
    excentury::print_inputs(argv, xc_input);
    excentury::STextInterface<excentury::load_mode> XC_LI_(argv[1]);
    std::string msg; XC_LI_.load(msg);
    XC_LI_.close();

    fprintf(stderr, "%s\n", msg.c_str());

    excentury::TextInterface<excentury::dump_mode> XC_DI_(stdout);
    
    XC_DI_.close();
}
// EPILOG FOR THE WHOLE FILE
