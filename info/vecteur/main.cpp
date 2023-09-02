
#include "ex3.h"

int main() {
    auto tab = new point[10];

    point p = tab[0];
    for (int i=0; i<10; i++){
        p = p + tab[i];
    }
    std::cout << (p / (float)10);
}
