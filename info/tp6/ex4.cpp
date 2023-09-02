//
// Created by Administrateur on 07/11/2022.
//

#include "ex1.h"

void exo4 () {

    std::vector<int> vect = {7, 1, 4, 0, -1};
    auto r =  std::min_element(vect.begin(), vect.end());
    if(*r < 0) std::cout << "toutes les valeurs ne sont pas positives" <<std::endl;
    std::replace_if(vect.begin(), vect.end(), [](int i){return std::signbit(i);}, 0);
    for (auto value : vect){
        std::cout << value << std::endl;
    }
    //std::istream_iterator<int>(vect);
    //std::ostream_iterator<int>(std::cout, ",");
}
