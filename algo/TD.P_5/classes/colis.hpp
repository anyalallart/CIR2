#pragma once
#include "objets.hpp"
using namespace std;

typedef struct SolColis
{
    vector<objet> objets;
    int benef = INT32_MIN;
    int conso = INT32_MAX;
} solColis;

class Colis
{
private:
    int capacite, nombreObj;
    vector<objet> objets;

public:
    Colis(const string &path);
    Colis() : capacite(0){};
    solColis getBestShipment();
    solColis getBestShipmentRepl(const string &filename);
    void genShipment(int capacite, int nombreObj, const string &filePath);
    friend ostream &operator<<(ostream &os, Colis &colis);
};