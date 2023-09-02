//
// Created by Administrateur on 07/11/2022.
//

#include "ex1.h"

void ex5(){
    std::map<std::string, int> m {{"Janvier", 1}, {"Fevrier", 2}, {"Mars", 3}, {"Avril", 4}, {"Mai", 5}, {"Juin", 6}, {"Juillet", 7}, {"Aout", 8}, {"Septembre", 9}, {"Octobre", 10}, {"Novembre", 11}, {"Decembre", 12}};

    for (const auto& value : m){
        std::cout << value.first << " " << value.second << std::endl;
    }

    std::vector<std::string> d {"24", "Decembre", "2004"};

    std::cout << d[0]<< "/" << m[d[1]] << "/" << d[2];
}