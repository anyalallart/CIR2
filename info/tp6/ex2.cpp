//
// Created by Administrateur on 07/11/2022.
//

#include "ex1.h"
#include "frac.h"

void exo2(){
    std::vector<Fraction> f;

    std::ifstream monFlux("frac.txt");
    if(monFlux.is_open()) {
        char val;
        int temp;
        bool test = true;

        while (monFlux) {
            val = monFlux.get();
            if (val != ' ' && val != '\n' && val != '/') {
                int number = val - '0';
                if (test) {
                    temp = number;
                    test = false;
                } else {
                    test = true;
                    Fraction *frac = new Fraction(temp, number);
                    // table.push_back(*frac);
                    f.push_back(*frac);
                }
            }
        }
    }
    else{
        std::cout << "oui";
    }
    monFlux.close();

    Fraction sum;
    Fraction test; // 0/1
    Fraction max;
    Fraction min;
    for (auto elem : f){
        sum+=elem;
        if (elem > max) max = elem;
        //if(elem < min)
        //if (elem < test) f.erase(elem, elem);
    } ;
    std::cout << sum;

}