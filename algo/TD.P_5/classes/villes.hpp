#pragma once
#include "objets.hpp"
using namespace std;

typedef struct SolVille
{
    vector<string> tournee;
    int distanceTotale = INT32_MAX;
} solVille;

typedef struct Vec2
{
    int x, y;
} vec2;

class Villes
{
private:
    vector<string> nomVilles;
    vector<vector<int>> matriceDistance;
    int nbVilles;

public:
    Villes(const string &path);
    Villes() : nbVilles(0){};
    int getNbVilles() const;
    friend ostream &operator<<(ostream &os, Villes &villes);
    int getDistance(string &villeA, string &villeB);
    solVille getBestPath();
    int getTotalDistance(vector<string> &solution);
    solVille getBestPathRepl(const string &filename);
    void genVilles(int nbVilles, const string &nomFichier);
    void getBestPathPermut(int debut, int fin);
};