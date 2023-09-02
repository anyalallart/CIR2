#include <iostream>


class quadrupede{
private:
    std::string nom;

public:
    void set_nom(std::string &n){
        this->nom = n;
    }
    std::string quadrupede_get() const{
        return this->nom;
    }
    virtual void speak ()=0;
};


class chat : public quadrupede{
    void speak() {
        std::cout << "miaou" << std::endl;
    }
};

class chien : public quadrupede{
    void speak(){
        std::cout << "ouaf" << std::endl;
    }
};


int main() {
    quadrupede * brigand = new chat;
    quadrupede * malo = new chat;
    quadrupede * frane = new chien;
    quadrupede * laika = new chien;

    int n = 4;
    quadrupede *quadruped[] = {brigand, malo, frane, laika};

    for(int i = 0; i<n; i++){
        quadruped[i]->speak();
    }
}

