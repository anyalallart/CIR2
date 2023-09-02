//
// Created by Administrateur on 26/09/2022.
//
#include "class.h"

Point3D::Point3D() {
    this->x = rand() % 100;
    this->y = rand() % 100;
    this->z = rand() % 100;
}

Point3D::Point3D(const float &newx, const float &newy, const float &newz) {
    this->x = newx;
    this->y = newy;
    this->z = newz;
}

void Point3D::setXYZ(const float &newx, const float &newy, const float &newz) {
    this->x = newx;
    this->y = newy;
    this->z = newz;
}

void Point3D::setX(const float &newx) {
    this->x = newx;
}

void Point3D::setY(const float &newy) {
    this->y = newy;
}

void Point3D::setZ(const float &newz) {
    this->z = newz;
}

float Point3D::getX(){
    return this->x;
}

float Point3D::getY(){
    return this->y;
}

float Point3D::getZ(){
    return this->z;
}

void Point3D::print() const {
    std::cout << "les coordonnees du point sont :" << this->x <<"," << this-> y << "," << this->z << std::endl;
}

float Point3D::distanceTo(const Point3D &otherPoint3D) {
    return (float)sqrt(pow(this->x - otherPoint3D.x, 2) + pow(this->y - otherPoint3D.y, 2) + pow(this->z - otherPoint3D.z, 2));
}

