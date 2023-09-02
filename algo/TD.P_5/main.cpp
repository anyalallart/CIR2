#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#include <map>
#include <filesystem>
#include <string>

#include "classes/objets.hpp"
#include "classes/colis.hpp"
#include "classes/villes.hpp"

using namespace std;

int main(int argc, char **argv)
{
    // Mauvais paramètres de lancement
    if (argc != 4 && argc != 3 && argc != 7)
    {
        cerr << "Formats corrects:" << endl;
        cout << "./TP5 graine fichier_colis.txt fichier_villes.txt" << endl;
        cout << "./TP5 -1 fichier_resultat.txt fichier_villes.txt" << endl;
        cout << "./TP5 -2 capacite nombre_obj p1.txt nombre_villes p2.txt" << endl;
        return EXIT_FAILURE;
    }
    // Mode génération meilleure solution
    else if (argc == 4 && atoi(argv[1]) == -1)
    {
        Colis colisObj;
        Villes villesObj;
        string pathRes = argv[2];

        if (!filesystem::exists(pathRes))
        {
            cerr << "Erreur le fichier n'existe pas, veuillez vérifier" << endl;
            return EXIT_FAILURE;
        }

        auto sol = colisObj.getBestShipmentRepl(pathRes);
        cout << 0 << " " << sol.benef << " " << sol.conso << " ";
        for (auto &it : sol.objets)
            cout << it.index << " " << it.conso << " " << it.benefice << " ";

        auto solRep = villesObj.getBestPathRepl(pathRes);
        for (auto &it : solRep.tournee)
            cout << it << " ";
        cout << solRep.distanceTotale << endl;

        Villes villesPermut(argv[3]); 
        villesPermut.getBestPathPermut(0, villesPermut.getNbVilles()-1);

        return EXIT_SUCCESS;
    }
    // Mode génération fichiers
    else if (argc == 7 && atoi(argv[1]) == -2)
    {
        Colis colisObj;
        Villes villesObj;
        string pathP1 = argv[2];
        string pathP2 = argv[3];

        colisObj.genShipment(atoi(argv[2]), atoi(argv[3]), argv[4]);
        villesObj.genVilles(atoi(argv[5]), argv[6]);

        return EXIT_SUCCESS;
    }

    // Seed
    unsigned int seed = atoi(argv[1]);
    srand(seed);

    // On récupère les deux arguments
    string pathColis = argv[2];
    string pathVilles = argv[3];

    // Si les fichiers n'existent pas
    if (!filesystem::exists(pathColis) || !filesystem::exists(pathVilles))
    {
        cerr << "Erreur un des fichiers n'existe pas, veuillez vérifier" << endl;
        return EXIT_FAILURE;
    }

    Colis colisObj(pathColis);
    Villes villesObj(pathVilles);

    // output de la forme: seed benef conso objet1 objet2 ... objet_n ville1 ville2 ... ville_n distance
    cout << seed << " ";
    auto sol = colisObj.getBestShipment();
    cout << sol.benef << " " << sol.conso << " ";
    for (auto &it : sol.objets)
        cout << it.index << " " << it.conso << " " << it.benefice << " ";

    auto sol2 = villesObj.getBestPath();
    for (auto &it : sol2.tournee)
        cout << it << " ";
    cout << sol2.distanceTotale << endl;

    return EXIT_SUCCESS;
}