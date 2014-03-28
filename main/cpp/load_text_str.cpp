#include <excentury/excentury.h>
#include "objects.h"

namespace xc = excentury;

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: ENTER ONLY ONE ARGUMENT...\n");
        exit(1);
    }
    char v_char;
    signed char v_byte;
    unsigned char v_ubyte;
    short int v_short;
    int v_int;
    long int v_long;
    unsigned short int v_ushort;
    unsigned int v_uint;
    unsigned long int v_ulong;
    float v_float;
    double v_double;
    std::string v_str;
    
    Point point_obj;
    Line line_obj;
    std::vector<Point> array_obj;
    std::vector<double> tensor_obj;
    
    xc::STextInterface<xc::load_mode> text_obj(argv[1]);
    #define LOAD(v) text_obj.load(v)
    LOAD(v_char);
    LOAD(v_byte);
    LOAD(v_ubyte);
    LOAD(v_short);
    LOAD(v_int);
    LOAD(v_long);
    LOAD(v_ushort);
    LOAD(v_uint);
    LOAD(v_ulong);
    LOAD(v_float);
    LOAD(v_double);
    LOAD(v_str);
    LOAD(point_obj);
    LOAD(line_obj);
    text_obj.load(array_obj, array_obj[0]);
    text_obj.load(tensor_obj, tensor_obj[0]);
    text_obj.close();
    
    #define PRINT(v) std::cout << #v << ": " << v << "\n";
    PRINT(v_char);
    PRINT((int)v_byte);
    PRINT((int)v_ubyte);
    PRINT(v_short);
    PRINT(v_int);
    PRINT(v_long);
    PRINT(v_ushort);
    PRINT(v_uint);
    PRINT(v_ulong);
    PRINT(v_float);
    PRINT(v_double);
    PRINT(v_str);
    printf("point_obj: Point(%f, %f)\n", point_obj.x, point_obj.y);
    printf("line_obj: [Point(%f, %f), Point(%f, %f)]\n", 
            line_obj.a.x, line_obj.a.y, line_obj.b.x, line_obj.b.y);
    printf("array_obj: \n");
    for (int i=0; i < array_obj.size(); ++i) {
        printf("  Point(%f, %f)\n", array_obj[i].x, array_obj[i].y);
    }
    printf("tensor_obj: \n");
    for (int i=0; i < tensor_obj.size(); ++i) {
        printf("  %f\n", tensor_obj[i]);
    }
}
