//
// Created by Administrateur on 03/10/2022.
//

#include "circl.h"

#include <iostream>
#include <cmath>

#pragma once
class Shape{
private:
    const int id = 0;// index to be initialized

protected:
    int color;
    int getId() const;

public: // constructor
    int get_color() const;
    void set_color(const int &c);
};

int Shape::getId() const {
    return this->id;
}

int Shape::get_color() const {
    return this->color;
}

void Shape::set_color(const int &c) {
    this->color = c;
}

class Circle: public Shape{
    private: float radius;
    public: //constructor
        float get_radius() const;
        void set_radius(const float &r);
        float get_area() const;
        float get_perimeter() const;
        void print() const;
};

float Circle::get_radius() const {
    return this->radius;
}

void Circle::set_radius(const float &r) {
    this->radius = r;
}

float Circle::get_area() const {
    return M_PI*this->radius*this->radius;
}

float Circle::get_perimeter() const {
    return static_cast<float>(2)*M_PI*this->radius;
}

void Circle::print() const {
    std::cout << "rayon" << this->radius << "aire" << get_area() << "perimetre" << get_perimeter() << std::endl;
}
