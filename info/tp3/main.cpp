
#include <iostream>
#include "trajectory.h"
#include "Vector.h"

int main() {
    srand(time(0));
    /*Point3D test;
    test.print();
    test.setXYZ(1,2,3);
    test.print();
    Point3D test2;
    std::cout << test.distanceTo(test2);
    Trajectory test;
    test.print();
    test.getPoint(3).print();
    std::cout << test.getTotalDistance();
    test.droite();
    test.print();*/
    My_vector test(1);
    test.set_an_element(1, 4);
    test.set_an_element(2, 3);
    test.get_an_element(2);
    test.push(2);
}
