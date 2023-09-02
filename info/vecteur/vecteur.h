//
// Created by Administrateur on 05/10/2022.
//

#ifndef UNTITLED3_VECTEUR_H
#define UNTITLED3_VECTEUR_H

#endif //UNTITLED3_VECTEUR_H
#include <iostream>

class Mon_vecteur{
    int size_ = 0;
    float* tab_;
public:
    explicit Mon_vecteur(const int &size);
    int get_size() const;
    float &operator()(const int &ind);//retourne le ième élément de tab_
    float operator*(Mon_vecteur &v);//produit scalaire de 2 vecteurs
    Mon_vecteur &operator*=(const float& val);// produit d'un vecteur par un scalaire
    friend std::ostream &operator<<(std::ostream&os,Mon_vecteur&v);
    ~Mon_vecteur();
};
Mon_vecteur::Mon_vecteur(const int &size) : size_(size),tab_(new float[size]) {
    this->size_ = size;
}

int Mon_vecteur::get_size() const {
    return this->size_;
}

float &Mon_vecteur::operator()(const int &ind) {
    return this->tab_[ind];
}

float Mon_vecteur::operator*(Mon_vecteur &v) {
    float result = 0;
    for(int i=0; i<this->size_; i++){
        result += this->tab_[i] * v.tab_[i];
    }
    return result;
}

Mon_vecteur &Mon_vecteur::operator*=(const float &val) {
    auto *result = new Mon_vecteur(this->size_);
    for(int i=0; i<this->size_; i++){
        result->tab_[i] = this->tab_[i] * val;
    }
    return *result;
}

std::ostream &operator<<(std::ostream &os, Mon_vecteur &v) {
    for(int i=0; i<v.size_ ; i++){
        std::cout << v.tab_[i] << std::endl;
    }
}

Mon_vecteur::~Mon_vecteur() {
    free (this->tab_);
}

