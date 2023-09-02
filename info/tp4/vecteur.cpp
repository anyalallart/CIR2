//
// Created by Administrateur on 03/10/2022.
//

#include "vecteur.h"
#include <iostream>

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

vecteur::vecteur() {
    this->co1 = 0;
    this->co2 = 1;
}

vecteur::vecteur(point p1, point p2) {
    this->co1 = p1.getX() - p2.getX();
    this->co2 = p1.getY() - p2.getY();
}

vecteur::vecteur(float c1, float c2) {
    this->co1 = c1;
    this->co2 = c2;
}

float vecteur::getc1() const {
    return this->co1;
}

float vecteur::getc2() const {
    return this->co2;
}

vecteur vecteur::sum(vecteur &v2) const {
    return vecteur{this->co1 + v2.getc1(), this->co2 + v2.getc2()};
}

bool vecteur::equal(vecteur &v2) const {
    return (this->co1 == v2.getc1() && this->co2 == v2.getc2());
}

vecteur vecteur::prod(float r) const {
    return vecteur{this->co1 * r, this->co2 * r} ;
}

/*void vecteur::set1(const point p1) {
    this->co1 = p1.getX() - p1.getX();
}

void vecteur::set2(const point p2) {
    this->co2 = p0.getY() - p1.getY();
}*/

float polygone::aire() {
    float s = 0;
    for(int i =0; i<this->nb-1; i++){
        s+= sommet[i].getX() * sommet[i+1].getY() - sommet[i+1].getX() * sommet[i].getY();
    }
    return s;
}

polygone::polygone(int n) {
    this->nb = n;
    this->sommet = new point[this->nb];
    for(int i =0; i<this->nb; i++){
        this->sommet[i]= point();
    }
}

void polygone::set_v(int p, float x, float y) {
    this->sommet[p].setX(x);
    this->sommet[p].setX(y);

}

void polygone::print() const {
    for(int i =0; i<this->nb; i++){
        std::cout << sommet[i];
    }
}
