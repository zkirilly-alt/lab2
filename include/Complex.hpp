#pragma once
#include <iostream>
#include <cmath>
#include <string>

class Complex {
private:
    double re;
    double im;

public:
    Complex(double real = 0.0, double imag = 0.0) : re(real), im(imag) {}

    double real() const { return re; }
    double imag() const { return im; }
    void real(double r) { re = r; }
    void imag(double i) { im = i; }

    double norm() const { return re*re + im*im; }
    double abs() const { return std::sqrt(norm()); }

    Complex& operator+=(const Complex& other) {
        re += other.re;
        im += other.im;
        return *this;
    }
    Complex& operator-=(const Complex& other) {
        re -= other.re;
        im -= other.im;
        return *this;
    }
    Complex& operator*=(const Complex& other) {
        double r = re*other.re - im*other.im;
        double i = re*other.im + im*other.re;
        re = r; im = i;
        return *this;
    }
    Complex& operator/=(const Complex& other) {
        double denom = other.re*other.re + other.im*other.im;
        if (denom == 0) throw std::runtime_error("Деление на ноль");
        double r = (re*other.re + im*other.im) / denom;
        double i = (im*other.re - re*other.im) / denom;
        re = r; im = i;
        return *this;
    }

    friend Complex operator+(Complex lhs, const Complex& rhs) { return lhs += rhs; }
    friend Complex operator-(Complex lhs, const Complex& rhs) { return lhs -= rhs; }
    friend Complex operator*(Complex lhs, const Complex& rhs) { return lhs *= rhs; }
    friend Complex operator/(Complex lhs, const Complex& rhs) { return lhs /= rhs; }

    Complex& operator*=(double scalar) {
        re *= scalar;
        im *= scalar;
        return *this;
    }
    Complex& operator/=(double scalar) {
        if (scalar == 0) throw std::runtime_error("Деление на ноль");
        re /= scalar;
        im /= scalar;
        return *this;
    }
    friend Complex operator*(Complex lhs, double scalar) { return lhs *= scalar; }
    friend Complex operator*(double scalar, Complex rhs) { return rhs *= scalar; }
    friend Complex operator/(Complex lhs, double scalar) { return lhs /= scalar; }

    bool operator==(const Complex& other) const { return re == other.re && im == other.im; }
    bool operator!=(const Complex& other) const { return !(*this == other); }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.re << (c.im >= 0 ? "+" : "") << c.im << "i)";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        is >> c.re >> c.im;
        return is;
    }

    std::string to_string() const {
        return "(" + std::to_string(re) + (im >= 0 ? "+" : "") + std::to_string(im) + "i)";
    }
};