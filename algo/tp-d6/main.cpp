#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int TAILLEDUGRAPHE = 6;
const int INFINI = 9999999;

std::vector<string> vecSommets;
int arcs [TAILLEDUGRAPHE][TAILLEDUGRAPHE];
int cheminCourt [TAILLEDUGRAPHE][TAILLEDUGRAPHE];
int pointChemin [TAILLEDUGRAPHE][TAILLEDUGRAPHE];


void Floyd_Warshall(){
    for(int sommetInt = 0; sommetInt < TAILLEDUGRAPHE; sommetInt++){
        for (int origine = 0; origine < TAILLEDUGRAPHE; origine++){
            for (int dest = 0; dest < TAILLEDUGRAPHE; dest++){
                if (cheminCourt[origine][sommetInt] + cheminCourt[sommetInt][dest] < cheminCourt[origine][dest]){
                    cheminCourt[origine][dest] = cheminCourt[origine][sommetInt] + cheminCourt[sommetInt][dest];
                    pointChemin[origine][dest] = sommetInt;
                }
            }
        }
    }
}

void afficherChemin (int sommet1, int sommet2, bool & premier)
{
    int suivant = pointChemin[sommet1][sommet2];
    if (suivant==-1 || sommet1 == sommet2 || suivant == sommet1 || suivant == sommet2)
        return;
    afficherChemin (sommet1, suivant, premier);
    if (premier) {
        std::cout << " \t\t par ";
        premier = false; }
    else {
        std::cout << " et "; }
    std::cout << vecSommets[suivant];
    afficherChemin (suivant, sommet2, premier);
}

void affichagePPCH(){
    for(int i = 0; i < TAILLEDUGRAPHE; i++) {
        for (int j = 0; j < TAILLEDUGRAPHE; j++) {
            if (pointChemin[i][j] != -1){
                bool t = true;
                cout << "Sommets intermediaires du PCCh de " << cheminCourt[i][j] << "km, (s'ils existent) de " << vecSommets[i] << " vers " << vecSommets[j];
                cout << endl;
                afficherChemin(i,j,t);
                cout << endl;
            }
        }
    }
}


int main() {
    vecSommets.push_back ("Lille");
    vecSommets.push_back ("Lens");
    vecSommets.push_back ("Paris");
    vecSommets.push_back ("Bourges");
    vecSommets.push_back ("Clermont-Ferrand");
    vecSommets.push_back ("Montpellier");

    for (int i = 0; i < TAILLEDUGRAPHE; i++){
        for (int j = 0; j < TAILLEDUGRAPHE; j++){
            arcs[i][j] = INFINI;
        }
    }

    arcs[0][1] = 40; //lille lens
    arcs[0][2] = 230; // lille paris
    arcs[1][2] = 200; // lens paris
    arcs[2][3] = 250; //paris bourges
    arcs[2][4] = 425; // paris cl
    arcs[3][4] = 190; // bourges cl
    arcs[4][5] = 300; //cl mont

    for (int id1 = 0; id1 < TAILLEDUGRAPHE; id1++){
        for (int id2 = 0; id2 < TAILLEDUGRAPHE; id2++){
            cheminCourt[id1][id2] = arcs[id1][id2];
            if (arcs[id1][id2] != INFINI){
                pointChemin[id1][id2] = id1;
            }
            else{
                pointChemin[id1][id2] = -1;
            }
        }
    }

    Floyd_Warshall();
    bool oui = true;
    affichagePPCH();

    return 0;
}
