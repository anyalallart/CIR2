//
// Created by Administrateur on 26/09/2022.
//

#include"class.h"



class Trajectory{
private:
    Point3D* points;
    int numberOfPoints=10;

public:
    explicit Trajectory(const int &t = 10);
    void print(); //print the coordinates of all points
    Point3D &getPoint(const int &n);//returns the reference of point n
    float getTotalDistance();
    void droite();
    ~Trajectory();
};

