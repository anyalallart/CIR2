//
// Created by Administrateur on 10/10/2022.
//

#include "fract.h"

void Fraction::print() const {
    std::cout << num << "/" << den << std::endl;
}

Fraction::Fraction() {
    std::cout << "Fraction()builds0/1" << std::endl;
    /* *this->num=0;
     * *this->den=1;*/
}

Fraction::Fraction(int num,int den){
    std::cout << "Fraction(int,int)builds" << num << "/" << den << std::endl;
    setNum(num);
    setDen(den);
}

Fraction Fraction::operator+(const Fraction & other) const {
    Fraction result;
    result.num = this->num*other.den + other.num*this->den;
    result.den = this->den + other.den;
    return result;
}

Fraction Fraction::operator-(const Fraction &other) const {
    Fraction result;
    result.num = this->num*other.den - other.num*this->den;
    result.den = this->den + other.den;
    return result;
}

Fraction Fraction::operator*(const Fraction &other) const {
    Fraction result;
    result.num = this->num * other.num;
    result.den = this->den * other.den;
    return result;
}

Fraction Fraction::operator/(const Fraction &other) const {
    Fraction result;
    result.num = this->num*other.den;
    result.den = this->den * other.num;
    return result;
}

Fraction Fraction::operator+=(const Fraction &other) {
    this->num = this->num*other.den + other.num*this->den;
    this->den = this->den + other.den;
    return *this;
}

bool Fraction::operator==(const Fraction &other) const {
    return (this->num % other.num == 0 && this->den % other.den == 0);
}

bool Fraction::operator!=(const Fraction &other) const {
    return !(this->num % other.num == 0 && this->den % other.den == 0);
}

bool Fraction::operator>(const Fraction &other) const {
    int n = this->num*other.den - other.num*this->den;
    int d = this->den + other.den;
    return (n > 0 || d > 0);
}

bool Fraction::operator<(const Fraction &other) const {
    int n = this->num*other.den - other.num*this->den;
    int d = this->den + other.den;
    return (n < 0 || d < 0);
}

bool Fraction::operator>=(const Fraction &other) const {
    int n = this->num*other.den - other.num*this->den;
    int d = this->den + other.den;
    return (n >= 0 || d >= 0);
}

bool Fraction::operator<=(const Fraction &other) const {
    int n = this->num*other.den - other.num*this->den;
    int d = this->den + other.den;
    return (n <= 0 || d <= 0);
}

std::ostream &operator<<(std::ostream &os, const Fraction &other) {
    return os << other.num << "/" << other.den << std::endl ;
}

std::istream &operator>>(std::istream &is, Fraction &other) {
    std::cout << "donnez numerateur";
    is >> other.num;
    std::cout << "donnez denominateur";
    is >> other.den;
    return is;
}







