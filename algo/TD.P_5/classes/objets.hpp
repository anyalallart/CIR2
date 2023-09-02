#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Définit nos structures et quelques fonction utiles

typedef struct Objet
{
    // (pas d'index car on le retrouve dans le vecteur ci-dessous)
    int index, conso, benefice;
    float ratio; // ratio bénéfice/conso

    friend ostream &operator<<(ostream &os, struct Objet &obj)
    {
        os << "\tIndex: " << obj.index << endl;
        os << "\tConsommation: " << obj.conso << endl;
        os << "\tBénéfice: " << obj.benefice << endl;
        os << "\tRatio Bénéf/Conso: " << obj.ratio << endl
           << endl;

        return os;
    }

    bool operator==(struct Objet obj)
    {
        return (this->index == obj.index);
    }
} objet;

vector<string> split(const string &str, char delimiter);

int rangedRand(int min, int max);