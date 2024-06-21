#pragma once

#include <iostream>

class Complex {
private:
    double _re;
    double _im;

public:
    Complex(const double& re = 0.0, const double& im = 0.0); // Constructor.

    double re() const; //get the real part of the complex number
    double im() const; //get the imaginary part of the complex number

    // Unary operators
    bool operator!() const; // Logical NOT
    Complex operator-() const; // Unary minus

    // Binary operators
    Complex operator+(const Complex& other) const;  // Binary plus +
    Complex& operator+=(const Complex& other);  // Plus +=
    Complex& operator-=(const Complex& other);  // Minus -=
    Complex& operator*=(const Complex& other);  // Multiply *=
    Complex& operator++();  // prefix increment
    Complex operator++(int);  // postfix increment

    // Comparison operators
    bool operator<(const Complex& other) const;
    bool operator>(const Complex& other) const;

    // friend global binary operators
    friend Complex operator-(const Complex& c1, const Complex& c2);  // global binary minus -
    friend Complex operator*(const Complex& c1, const Complex& c2);  // global binary multiply *
    friend bool operator==(const Complex& c1, const Complex& c2);  // global binary equal ==
    friend bool operator!=(const Complex& c1, const Complex& c2);  // global binary not equal !=

    // friend global IO operators
    friend std::ostream& operator<<(std::ostream& output, const Complex& c);  // global output operator
    friend std::istream& operator>>(std::istream& input, Complex& c);  // global input operator

};

