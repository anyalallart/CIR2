#include <iostream>
#include "vecteur.h"

int main() {
    polygone p(4);
    p.set_v(0,1,1);
    p.set_v(1,1,2);
    p.set_v(2,2,2);
    p.set_v(3,2,1);
    std::cout << p.aire();
}

