//
// Created by Administrateur on 20/09/2022.
//

#include "class.h"



void TextRectangle::set(int w, int h){
    if (w>10 || w<0 || h>10 || h<0) {
        cerr << "les valeurs doivent etre postitive et plus petite que 10" << endl;
    }
    else {
        this->set_w(w);
        this->set_h(h);
    }
}

void TextRectangle::set_w(int w){
    this->widht = w;
}

void TextRectangle::set_h(int h){
    this->height = h;
}

int TextRectangle::get_w() const{
    return widht;
}

int TextRectangle::get_h() const{
    return height;
}

int TextRectangle::getArea() const{
    return widht*height;
}

int TextRectangle::getPerimeter() const{
    return (widht*2) + (height*2);
}

void TextRectangle::print() const{
    cout << "widht :" << this->get_w() << endl;
    cout << "height :" << TextRectangle::get_h() << endl;
    cout << "area :" << TextRectangle::getArea() << endl;
    cout << "perimeter :" << TextRectangle::getPerimeter() << endl;
}

void TextRectangle::drawPerimeter(char pattern) const{
    for (int i=0; i<widht; i++) {
        cout << pattern << ' ';
    }
    cout << endl;
    for(int j=0; j<height-2; j++){
        cout << pattern;
        for(int k=0; k<(widht*2) -3; k++){
            cout << ' ';
        }
        cout << pattern << endl;
    }
    for (int i=0; i<widht; i++) {
        cout << pattern << ' ';
    }
    cout << endl;
    cout << endl;
}

void TextRectangle::drawArea(char pattern) const{
    for (int i=0; i<widht; i++) {
        cout << pattern << ' ';
    }
    cout << endl;
    for(int j=0; j<height-2; j++){
        for(int k=0; k<widht -1; k++){
            cout << pattern << ' ';
        }
        cout << pattern << endl;
    }
    for (int i=0; i<widht; i++) {
        cout << pattern << ' ';
    }
    cout << endl;
}