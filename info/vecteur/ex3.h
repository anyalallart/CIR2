//
// Created by Administrateur on 10/10/2022.
//
#include <iostream>
#include <random>

class point{
private:
    float x,y;
public:
    explicit point();
    explicit point(float &x, float &y){this->x=x; this->y=y;};
    void setXYZ(const float &newx, const float &newy);
    void setX(const float &newx);
    void setY(const float &newy);
    float getX() const;
    float getY() const;
    friend std::istream& operator>>(std::istream& is, point& other);
    friend std::ostream& operator<<(std::ostream& os, const point& other);
    point operator+(const point &other);
    float operator*(const point &other);
    float operator*(float other);
    point operator|(const point &other);
    point operator/(const float &other);
};
