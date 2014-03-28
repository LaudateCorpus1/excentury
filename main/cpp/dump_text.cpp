#include <excentury/excentury.h>
#include "objects.h"

namespace xc = excentury;

int main() {
    char v_char = 'A';
    signed char v_byte = 127;
    unsigned char v_ubyte = 255;
    short int v_short = 2;
    int v_int = 10;
    long int v_long = 123456789;
    unsigned short int v_ushort = 2;
    unsigned int v_uint = 10;
    unsigned long int v_ulong = 123456789;
    float v_float = 3.14;
    double v_double = 0.007;
    std::string v_str = "hello world";
    
    Point point_obj(34.1, 4);
    Line line_obj(100, 200, 300, 400);
    
    std::vector<Point> array_obj(2);
    array_obj[0].x = 1;
    array_obj[0].y = 0;
    array_obj[1].x = 2;
    array_obj[1].y = 4;
    
    std::vector<double> tensor_obj(4);
    tensor_obj[0] = 1;
    tensor_obj[1] = 2;
    tensor_obj[2] = 3;
    tensor_obj[3] = 4;
    
    xc::TextInterface<xc::dump_mode> text_obj("tmp.xc");
    #define DUMP(v) text_obj.dump(v, #v)
    DUMP(v_char);
    DUMP(v_byte);
    DUMP(v_ubyte);
    DUMP(v_short);
    DUMP(v_int);
    DUMP(v_long);
    DUMP(v_ushort);
    DUMP(v_uint);
    DUMP(v_ulong);
    DUMP(v_float);
    DUMP(v_double);
    DUMP(v_str);
    DUMP(point_obj);
    DUMP(line_obj);
    text_obj.dump(array_obj, "array_obj", array_obj[0]);
    text_obj.dump(tensor_obj, "tensor_obj", tensor_obj[0]);
    text_obj.close();
}
