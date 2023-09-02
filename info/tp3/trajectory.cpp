//
// Created by Administrateur on 26/09/2022.
//
#include <iostream>
#include "trajectory.h"

void Trajectory::print() {
    for (int i=0; i<this->numberOfPoints ; i++){
        points[i].print();
    }
}

Point3D &Trajectory::getPoint(const int &n) {
    return points[n-1];
}

float Trajectory::getTotalDistance() {
    float d = 0;
    for (int i=0; i<this->numberOfPoints-1 ; i++){
        d+= points[i].distanceTo(points[i+1]);
    }
    return d;
}

void Trajectory::droite() {
    float t = points[0].distanceTo(points[this->numberOfPoints-1]);
    float step = t / (float)this->numberOfPoints;

    for(int i = 0; i<this->numberOfPoints; i++){
        points[i].setXYZ(points[0].getX()+ (float)i*step, points[0].getY()+ (float)i*step, points[0].getZ() + (float)i*step);
    }
}

Trajectory::Trajectory(const int &t) {
    this->numberOfPoints = t;
    this->points = new Point3D[t];
}

Trajectory::~Trajectory(){
    delete this->points;
}


