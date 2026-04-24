#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>     // 数学函数
#include <iomanip>   // 控制输出格式
#include <iostream>  // 输入输出
#include <stdexcept> // 异常处理
// 你不可以使用任何其他的头文件!

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override {
    return "complex divided by zero!";
  }
};

// 用于判断浮点数的符号.
inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

// 请保留所有的接口声明，即使你没有实现它们。
// 否则可能出现编译错误，无法通过部分测试点。
// TODO 补全类的实现
class complex {
private:
  double a, b; // a + bi
public:
  // Default constructor: 0+0i
  complex() : a(0.0), b(0.0) {}
  
  // Constructor with real part only: a+0i
  complex(double a) : a(a), b(0.0) {}
  
  // Constructor with real and imaginary parts: a+bi
  complex(double a, double b) : a(a), b(b) {}
  
  // Return reference to real part
  double &real() {
    return a;
  }
  
  // Return reference to imaginary part
  double &imag() {
    return b;
  }
  
  // Return negative of complex number
  complex operator-() const {
    return complex(-a, -b);
  }
  
  // Return conjugate of complex number
  complex operator~() const {
    return complex(a, -b);
  }
  
  // Addition
  complex operator+(const complex &rhs) const {
    return complex(a + rhs.a, b + rhs.b);
  }
  
  // Subtraction
  complex operator-(const complex &rhs) const {
    return complex(a - rhs.a, b - rhs.b);
  }
  
  // Multiplication
  complex operator*(const complex &rhs) const {
    // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
    return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
  }
  
  // Division
  complex operator/(const complex &rhs) const {
    // Check if divisor is zero
    if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
      throw divided_by_zero();
    }
    
    // (a + bi) / (c + di) = (a + bi) * (c - di) / (c^2 + d^2)
    // = (ac + bd) / (c^2 + d^2) + (bc - ad) / (c^2 + d^2)i
    double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
    return complex(
      (a * rhs.a + b * rhs.b) / denominator,
      (b * rhs.a - a * rhs.b) / denominator
    );
  }
  
  // Compound assignment operators
  complex &operator+=(const complex &rhs) {
    a += rhs.a;
    b += rhs.b;
    return *this;
  }
  
  complex &operator-=(const complex &rhs) {
    a -= rhs.a;
    b -= rhs.b;
    return *this;
  }
  
  complex &operator*=(const complex &rhs) {
    // (a + bi) *= (c + di)
    // a = ac - bd
    // b = ad + bc
    double new_a = a * rhs.a - b * rhs.b;
    double new_b = a * rhs.b + b * rhs.a;
    a = new_a;
    b = new_b;
    return *this;
  }
  
  complex &operator/=(const complex &rhs) {
    // Check if divisor is zero
    if (std::abs(rhs.a) < 1e-6 && std::abs(rhs.b) < 1e-6) {
      throw divided_by_zero();
    }
    
    // (a + bi) / (c + di) = (a + bi) * (c - di) / (c^2 + d^2)
    double denominator = rhs.a * rhs.a + rhs.b * rhs.b;
    double new_a = (a * rhs.a + b * rhs.b) / denominator;
    double new_b = (b * rhs.a - a * rhs.b) / denominator;
    a = new_a;
    b = new_b;
    return *this;
  }
  
  // Equality comparison
  bool operator==(const complex &rhs) const {
    // Two complex numbers are equal if both real and imaginary parts are within 1e-6
    return std::abs(a - rhs.a) < 1e-6 && std::abs(b - rhs.b) < 1e-6;
  }
  
  // Conversion to bool
  explicit operator bool() const {
    // Return false if both real and imaginary parts are zero (within 1e-6)
    return !(std::abs(a) < 1e-6 && std::abs(b) < 1e-6);
  }
  
  // Output operator
  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
    // Save original flags and precision
    std::ios_base::fmtflags old_flags = os.flags();
    std::streamsize old_precision = os.precision();
    
    // Set fixed format and 6 decimal places
    os << std::fixed << std::setprecision(6);
    
    // Output real part
    if (x.a < -1e-6) {
      // Real part is negative
      os << x.a;
    } else if (x.a > 1e-6) {
      // Real part is positive
      os << x.a;
    } else {
      // Real part is zero (within 1e-6)
      os << "0.000000";
    }
    
    // Output imaginary part
    if (x.b < -1e-6) {
      // Imaginary part is negative
      os << "-" << std::abs(x.b) << "i";
    } else if (x.b > 1e-6) {
      // Imaginary part is positive
      os << "+" << x.b << "i";
    } else {
      // Imaginary part is zero (within 1e-6)
      os << "+0.000000i";
    }
    
    // Restore original flags and precision
    os.flags(old_flags);
    os.precision(old_precision);
    
    return os;
  }
};

} // namespace sjtu

#endif
