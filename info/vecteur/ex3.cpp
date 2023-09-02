//
// Created by Administrateur on 10/10/2022.
//

#include "ex3.h"


void point::setXYZ(const float &newx, const float &newy) {
    this->x = newx;
    this->y = newy;
}

void point::setX(const float &newx) {
    this->x = newx;
}

void point::setY(const float &newy) {
    this->y = newy;
}

float point::getX() const {
    return this->x;
}

float point::getY() const {
    return this->y;
}

std::ostream &operator<<(std::ostream &os, const point &other) {
    return os << other.x << "/" << other.y << std::endl ;
}

std::istream &operator>>(std::istream &is, point &other) {
    std::cout << "donnez x";
    is >> other.x;
    std::cout << "donnez y";
    is >> other.y;
    return is;
}

point point::operator+(const point &other) {
    point result;
    result.x = this->x + other.x;
    result.y = this->y + other.y;
    return result;
}

float point::operator*(const point &other) {
    float result;
    result= this->x * other.x + this->y * other.y;
    return result;
}

float point::operator*(float other) {
    float result;
    result= this->x * other + this->y * other;
    return result;
}

point point::operator|(const point &other) {
    point result;
    result.x= (this->x + other.x) /2;
    result.y = (this->y + other.y) / 2;
    return result;
}

point::point() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 100); // define the range

    this->x = (float)distr(gen);
    this->y = (float)distr(gen);
}

point point::operator/(const float &other) {
    point result;
    result.x= this->x / other;
    result.y = this->y / other;
    return result;
}




