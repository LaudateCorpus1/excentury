#include <excentury/excentury.h>

namespace xc = excentury;

int main() {
    xc::DynamicTensor<1, double, 1> v1(5);
    for (int i=1; i <= 5; ++i) v1[i] = i;
    v1.display(std::cout); std::cout << "\n";
    
    xc::DynamicTensor<2, double, 0, 0> v2_c(2, 3);
    xc::DynamicTensor<2, double, 0, 1> v2_r(2, 3);
    for (int i=0; i < 6; ++i) {
        v2_c[i] = i;
        v2_r[i] = i;
    }
    v2_c.display(std::cout); std::cout << "\n";
    v2_r.display(std::cout); std::cout << "\n";
    
    xc::DynamicTensor<3, double, 0, 0> v3_c(2, 3, 4);
    xc::DynamicTensor<3, double, 0, 1> v3_r(2, 3, 4);
    for (int i=0; i < 24; ++i) {
        v3_c[i] = i;
        v3_r[i] = i;
    }
    v3_c.display(std::cout); std::cout << "\n";
    v3_r.display(std::cout); std::cout << "\n";
    
    size_t size[4] = {2, 3, 4, 5};
    xc::DynamicTensor<4, double, 0, 0> v4_c(size);
    xc::DynamicTensor<4, double, 0, 1> v4_r(size);
    for (int i=0; i < 120; ++i) {
        v4_c[i] = i;
        v4_r[i] = i;
    }
    v4_c.display(std::cout); std::cout << "\n";
    v4_r.display(std::cout); std::cout << "\n";
}
