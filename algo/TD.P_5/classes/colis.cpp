#include "colis.hpp"
#include <algorithm>
using namespace std;

Colis::Colis(const string &path)
{
    ifstream file(path);

    if (file.is_open())
    {
        string buff;

        // Buff contient une ligne du fichier
        while (getline(file, buff))
        {
            auto str = split(buff, ' ');
            objet tmpObj;

            // Première ligne du fichier -> capacité et nombre obj
            if (str.size() == 2)
            {
                capacite = stoi(str[0]);
                nombreObj = stoi(str[1]);
                continue;
            }

            float ratio = stof(str[2]) / stof(str[1]); // ratio bénéfice/conso
            tmpObj = {stoi(str[0]), stoi(str[1]), stoi(str[2]), ratio};
            objets.push_back(tmpObj);
        }
        file.close();
    }
}

ostream &operator<<(ostream &os, struct Colis &colis)
{
    os << "Capacité: " << colis.capacite << endl;
    os << "Nombre d'objets: " << colis.nombreObj << endl;

    for (auto &obj : colis.objets)
    {
        os << obj;
    }
    return os;
}

solColis Colis::getBestShipment()
{
    int consoTotale = 0, benefTotal = 0;
    vector<objet> solution;

    // On trie le vector en fonction du ratio dans l'ordre décroissant
    sort(objets.begin(), objets.end(), [](objet objA, objet objB)
         { return objA.ratio > objB.ratio; });

    for (auto it = objets.begin(); it != objets.end() - 1; it++)
    {
        auto obj1 = *it;
        auto obj2 = *(it + 1);
        auto sol = obj1;

        // À optimiser, c'est dégueulasse
        // Si notre couple de solutions est invalide, on continue
        if (obj1.conso + consoTotale > capacite && obj2.conso + consoTotale > capacite)
            continue;
        // Si l'objet 1 prend trop de place, on sélectionne le deuxième
        if (obj1.conso + consoTotale > capacite)
            sol = obj2;
        // Si les deux objets vont, on en choisit un aléatoirement
        else if (obj2.conso + consoTotale <= capacite && obj1.conso + consoTotale <= capacite)
            sol = (rand() % 2 == 0) ? obj1 : obj2;
        // Sinon, sol ne change pas et reste obj1

        if (find(solution.begin(), solution.end(), sol) != solution.end())
            continue;

        // On ajoute l'objet sélectionné
        solution.push_back(sol);
        consoTotale += sol.conso;
        benefTotal += sol.benefice;
    }
    return {solution, benefTotal, consoTotale};
}

bool isAlpha(string &str)
{
    for (auto &chr : str)
    {
        if (!isalpha(chr))
            return false;
    }
    return true;
}

solColis Colis::getBestShipmentRepl(const string &filename)
{
    solColis sol;
    ifstream file(filename);

    if (!file.is_open())
        return sol;

    string buff;
    while (getline(file, buff))
    {
        // Découpe
        auto str = split(buff, ' ');
        solColis tmp;
        tmp.benef = stoi(str[1]);
        tmp.conso = stoi(str[2]);

        // On retire le dernier élément (kilométrage)
        str.pop_back();

        // On retire les 3 premiers éléments (seed, benef, conso)
        for (int i = 0; i < 3; i++)
            str.erase(str.begin());

        // On retire le nom des villes
        str.erase(remove_if(str.begin(), str.end(), isAlpha), str.end());

        for (auto it = str.begin(); it != str.end(); it += 3)
        {
            // On crée un objet temporaire
            objet tmpObj;
            tmpObj.index = stoi(*it);
            tmpObj.conso = stoi(*(it + 1));
            tmpObj.benefice = stoi(*(it + 2));
            tmpObj.ratio = (float)tmpObj.benefice / (float)tmpObj.conso;
            tmp.objets.push_back(tmpObj);
        }

        if (tmp.benef > sol.benef)
        {
            sol.benef = tmp.benef;
            sol.conso = tmp.conso;
            sol.objets = tmp.objets;
        }
    }
    file.close();

    return sol;
}

void Colis::genShipment(int capacite, int nombreObj, const string &filePath)
{
    objet tmpObj;

    objets.clear();
    this->capacite = capacite;
    this->nombreObj = nombreObj;

    for (int i = 1; i <= nombreObj; i++)
    {
        tmpObj.index = i;
        tmpObj.benefice = rangedRand(3, 15);
        tmpObj.conso = rangedRand(1, capacite);
        tmpObj.ratio = (float)(tmpObj.benefice) / (float)(tmpObj.conso);

        objets.push_back(tmpObj);
    }

    ofstream file(filePath);

    if (file.is_open())
    {
        // 1 ere ligne
        file << capacite << " " << nombreObj << endl;

        // On écrit chaque obj
        for (auto &obj : objets)
        {
            file << obj.index << " " << obj.conso << " " << obj.benefice << endl;
        }

        file.close();
    }

    cout << *this << endl;
}