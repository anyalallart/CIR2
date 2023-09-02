//
// Created by Administrateur on 20/09/2022.
//

#ifndef UNTITLED_CLASS_H
#define UNTITLED_CLASS_H

#endif //UNTITLED_CLASS_H
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class TextRectangle {
private:
    int widht;
    int height;

public:
    void set(int w, int h);
    void set_w(int w);
    void set_h(int h);
    int get_w() const;
    int get_h() const;
    int getArea() const;
    int getPerimeter() const;
    void print() const;
    void drawPerimeter(char pattern) const;
    void drawArea(char pattern) const;
};