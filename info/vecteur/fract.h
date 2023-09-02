//
// Created by Administrateur on 10/10/2022.
//

#include <iostream>
class Fraction {
private:
    int num=0;
    int den=1;
public:
    Fraction();
    Fraction(int num,int den);
    void print() const;
    Fraction plus(const Fraction &other) const;
    void setNum(int num){this->num=num;}
    void setDen(int den){this->den=den;}
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    Fraction operator+=(const Fraction& other);
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    bool operator>(const Fraction& other) const;
    bool operator<(const Fraction& other) const;
    bool operator>=(const Fraction& other) const;
    bool operator<=(const Fraction& other) const;
    friend std::istream& operator>>(std::istream& is, Fraction& other);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& other);
};