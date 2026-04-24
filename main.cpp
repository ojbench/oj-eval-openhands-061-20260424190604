
#include "complex.hpp"
#include <iostream>

int main() {
    // Test cases from the problem description
    sjtu::complex z; // z = 0;
    std::cout << "z = " << z << std::endl;
    
    sjtu::complex z1 = 1;        // z = 1;
    std::cout << "z1 = " << z1 << std::endl;
    
    sjtu::complex z2 = 2.22;     // z = 2.22;
    std::cout << "z2 = " << z2 << std::endl;
    
    sjtu::complex z3(114.514);   // z = 114.514;
    std::cout << "z3 = " << z3 << std::endl;
    
    sjtu::complex z4(1, 2);       // z = 1 + 2i;
    std::cout << "z4 = " << z4 << std::endl;
    
    sjtu::complex z5(2.22, 3.33); // z = 2.22 + 3.33i;
    std::cout << "z5 = " << z5 << std::endl;
    
    sjtu::complex x;     // x = 0;
    sjtu::complex y = x; // y = x = 0;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    
    x = y = 2; // x = y = 2;
    std::cout << "x = " << x << ", y = " << y << std::endl;
    
    // Test real() and imag()
    sjtu::complex z6(1, 2);
    std::cout << z6.real() << "," << z6.imag() << std::endl; // Output 1,2
    z6.real() = 3;
    z6.imag() = 4; // z = 3+4i
    std::cout << "z6 = " << z6 << std::endl;
    
    // Test comparison
    sjtu::complex a = 1, b = 2, c = 2;
    std::cout << (a == b) << std::endl; // Output 0
    std::cout << (b == c) << std::endl; // Output 1
    
    // Test bool conversion
    sjtu::complex a1; // Default initialized to 0
    if (a1) {
        std::cout << "a1 is not zero!" << std::endl;
    } else {
        std::cout << "a1 is zero!" << std::endl; // Output a1 is zero!
    }
    
    // Test unary operators
    sjtu::complex z7(1, 2);
    sjtu::complex z8 = -z7; // z8 = -1 - 2i
    std::cout << "z7 = " << z7 << ", -z7 = " << z8 << std::endl;
    
    sjtu::complex z9 = ~z7; // z9 = 1 - 2i
    std::cout << "z7 = " << z7 << ", ~z7 = " << z9 << std::endl;
    
    // Test arithmetic operations
    sjtu::complex p(1, 2), q(3, 4);
    std::cout << "p + q = " << p + q << std::endl;
    std::cout << "p - q = " << p - q << std::endl;
    std::cout << "p * q = " << p * q << std::endl;
    
    // Test division with exception
    sjtu::complex one = 1, zero = 0;
    try {
        sjtu::complex result = one / zero;
        std::cout << "Result: " << result << std::endl;
    } catch(const std::exception &err) {
        std::cout << err.what() << std::endl; // Should output "complex divided by zero!"
    }
    
    return 0;
}

