#include "class.h"

class MouleAMuffin{
private :
    std::string nom_gateau;
    bool auchocolat;
    double poids;
public:
    MouleAMuffin(std::string& nom, bool c, double p);
    MouleAMuffin(double in_poids, std::string& in_nomGateau);
};

MouleAMuffin::MouleAMuffin(std::string& nom, bool c, double p) {
    this->nom_gateau = nom;
    this->auchocolat = c;
    this->poids = p;
}

MouleAMuffin::MouleAMuffin(double in_poids, std::string& in_nomGateau) {
    this->nom_gateau = in_nomGateau;
    this->poids = in_poids;
    size_t choco = in_nomGateau.find("choco");
    if(choco) this->auchocolat = true;
    else this->auchocolat = false;
}


