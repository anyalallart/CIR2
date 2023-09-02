//
// Created by Administrateur on 27/09/2022.
//

#include "Vector.h"
#include "iostream"

My_vector::My_vector() {
    this->size = 0;
    this->tab = nullptr;
}

My_vector::My_vector(const size_t &size) {
    this->size = size;
    this->tab = (my_type *) realloc(this->tab, (this->size)*sizeof(my_type));
}

My_vector::My_vector(const My_vector &vector) {
    this->size = vector.size;
    this->tab = (my_type *) realloc(this->tab, (this->size)*sizeof(my_type));
    std::copy(this-> tab, tab+size, vector.tab);
}

My_vector::~My_vector() {
    delete this->tab;
}

const size_t &My_vector::get_size() const {
    return this->size;
}

void My_vector::set_an_element(const size_t &index, const my_type &val) {
    if (index > this->size){
        this->size += index;
        this->tab = (my_type *) realloc(this->tab, (this->size)*sizeof(my_type));
    }
    this->tab[index] = val;
}

const my_type &My_vector::get_an_element(const size_t &index) const {
    /*if (index >= this->size){
        std::cout << "0" << std::endl;
    }
    else
    {
        std::cout << this->tab[index] << std::endl;
    }*/

    std::cout << "Non" << std::endl;
    return 0;
}

void My_vector::push(const my_type &val) {
    /*this->size += 1;
    std::cout << this->size;
    this->tab = (my_type *) realloc(this->tab, (this->size)*sizeof(my_type));
    this->tab[this->size-1] = val;*/
    std::cout << "oui";
}

