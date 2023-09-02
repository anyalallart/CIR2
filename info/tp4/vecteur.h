//
// Created by Administrateur on 03/10/2022.
//

#ifndef TP4_VECTEUR_H
#define TP4_VECTEUR_H

#endif //TP4_VECTEUR_H
#include <iostream>

class point{
private:
    float x,y;
public:
    explicit point(){ x=0; y=0;};
    explicit point(float &x, float &y){this->x=x; this->y=y;};
    void setXYZ(const float &newx, const float &newy);
    void setX(const float &newx);
    void setY(const float &newy);
    float getX() const;
    float getY() const;
};

class vecteur{
private:
    float co1;
    float co2;
public:
    vecteur();
    vecteur(float c1, float c2);
    vecteur(point p1, point p2);
    /*void set1(const float &new1x, float &new1y);
    void set2(const float &new2x, float &new2y);*/
    float getc1() const;
    float getc2() const;
    vecteur sum(vecteur &v2) const;
    bool equal(vecteur &v2) const;
    vecteur prod(float r) const;
};

class polygone{
private:
    int nb;
    point *sommet;
public:
    explicit polygone(int n);
    float aire();
    void set_v(int p, float x, float y);
    void print() const;
};

