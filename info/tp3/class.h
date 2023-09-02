//
// Created by Administrateur on 26/09/2022.
//
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <random>

class Point3D{
private:
    float x,y,z;    //private attributes
public:
    //constuctors
    Point3D();//fill XYZ with random values (from 0 to 100)
    Point3D(const float &newx, const float &newy, const float &newz);//fill XYZ values

    // Setters and getters
    void setXYZ(const float &newx, const float &newy, const float &newz);
    void setX(const float &newx);
    void setY(const float &newy);
    void setZ(const float &newz);
    float getX();
    float getY();
    float getZ();

    //other methods
    void print() const; //prints the coordinates of the point
    float distanceTo(const Point3D &otherPoint3D);
};








