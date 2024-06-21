#include "Complex.hpp"
#include <cmath>
#include <sstream>

// Constructor
Complex::Complex(const double& re, const double& im) : _re(re), _im(im) {}

// Getters
double Complex::re() const {
    return _re;
}

double Complex::im() const {
    return _im;
}

// Unary operators
bool Complex::operator!() const {
    return _re == 0 && _im == 0;
}

Complex Complex::operator-() const {
    return Complex(-_re, -_im);
}

// Binary operators
Complex Complex::operator+(const Complex& other) const {
    return Complex(_re + other._re, _im + other._im);
}

Complex& Complex::operator+=(const Complex& other) {
    _re += other._re;
    _im += other._im;
    return *this;
}

Complex& Complex::operator-=(const Complex& other) {
    _re -= other._re;
    _im -= other._im;
    return *this;
}

Complex& Complex::operator*=(const Complex& other) {
    double new_re = _re * other._re - _im * other._im;
    double new_im = _re * other._im + _im * other._re;
    _re = new_re;
    _im = new_im;
    return *this;
}

// Prefix increment
Complex& Complex::operator++() {
    _re++;
    return *this;
}

// Postfix increment
Complex Complex::operator++(int) {
    Complex copy = *this;
    _re++;
    return copy;
}

bool Complex::operator<(const Complex& other) const {
    return std::hypot(_re, _im) < std::hypot(other._re, other._im);
}

bool Complex::operator>(const Complex& other) const {
    return std::hypot(_re, _im) > std::hypot(other._re, other._im);
}

// Friend global binary operators
Complex operator-(const Complex& c1, const Complex& c2) {
    return Complex(c1._re - c2._re, c1._im - c2._im);
}

Complex operator*(const Complex& c1, const Complex& c2) {
    return Complex(c1._re * c2._re - c1._im * c2._im,
                   c1._re * c2._im + c1._im * c2._re);
}

const float TOLERANCE = 0.001;

bool operator==(const Complex& c1, const Complex& c2) {
    return (std::abs(c1._re - c2._re) <= TOLERANCE && std::abs(c1._im - c2._im) <= TOLERANCE);
}

bool operator!=(const Complex& c1, const Complex& c2) {
    return !(c1 == c2);
}

// Friend global IO operators
std::ostream& operator<<(std::ostream& output, const Complex& c) {
    output << c._re << (c._im >= 0 ? '+' : '-') << std::abs(c._im) << 'i';
    return output;
}
std::istream& operator>>(std::istream& input, Complex& c) {
    double re = 0, im = 0;
    char ch1, ch2;

    if (input >> re >> ch1 >> im >> ch2 && ch2 == 'i') {
        if (ch1 == '+') {
            c._re = re;
            c._im = im;
        } else if (ch1 == '-') {
            c._re = re;
            c._im = -im;
        } else {
            input.setstate(std::ios::failbit);
        }
    } else {
        input.setstate(std::ios::failbit);
    }

    return input;
}