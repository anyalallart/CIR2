//
// Created by Administrateur on 08/11/2022.
//

#include "ex1.h"

void ex6(){
    std::map<std::string, std::string> m;

    std::fstream monFlux("accro.txt");
    if(monFlux.is_open()) {
        std::string l;
        while (getline(monFlux, l)) {
            m[l.substr(0, l.find('=')-1)] = l.substr(l.find('=')+2, l.size()-1);
        }
    }
    else{
        std::cout << "oui";
    }

    /*for (const auto& values : m){
        std::cout << values.second ;
    }*/

    bool c = true;
    while(c) {
        std::string s;

        std::cout << "donnez accronyme" << std::endl;
        std::cin >> s;

        if (s == "fin") {
            c = false;
        } else {
            if (m.find(s) != m.end()) {
                std::cout << m[s] << std::endl;
            } else {
                std::cout << "voulez-vous ajouter une definition ? (o/n)" << std::endl;
                char rep;
                std::cin >> rep;
                if (rep == 'o') {
                    std::cout << "donnez definition" << std::endl;
                    std::string def;
                    std::cin >> def;
                    monFlux << s << "=" << def << std::endl;
                }
            }
        }
    }
    monFlux.close();
}
