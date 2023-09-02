#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <cmath>
#include <array>
#include <algorithm>

using namespace std;

constexpr int codeASCIIde_a=97;
constexpr int codeASCIIde_A=65;
constexpr int nombreDeLettres=26;
constexpr int tailleMinNomVille=4;
constexpr int tailleMaxNomVille=12;
constexpr int grainePourLeRand=1;
constexpr int nombreDeVilles=4;
constexpr int nombreCombinaisons=24;
constexpr int tailleCoteCarte=100;
vector<pair<vector<string>,int>> toutesLesTourneesEtLeurDistanceTotale;

map<string,tuple<int,int,int>> ville_alea(){

    map<string,tuple<int,int,int>> maMapNomsVillesEtCoordonnees;

    srand(grainePourLeRand);

    for (int j = 0; j < nombreDeVilles; j++){
        int X = rand() % (100);
        int Y = rand() % (100);
        int nbLettresNomVille = tailleMinNomVille+rand()%(tailleMaxNomVille-tailleMinNomVille+1);
        string mot ="";
        char lettre = codeASCIIde_A + rand() % (nombreDeLettres);
        for (int i = 0; i < nbLettresNomVille; i++) {
            mot += lettre;
            lettre = codeASCIIde_a + rand() % (nombreDeLettres);
        }
        cout << j << X << Y << endl;
        auto monTuple= make_tuple(j, X, Y);
        maMapNomsVillesEtCoordonnees.insert(maMapNomsVillesEtCoordonnees.begin(),pair<string,tuple<int,int,int> >(mot,monTuple));
    }
    return maMapNomsVillesEtCoordonnees;
}

void aff_map(map<string,tuple<int,int,int>> map){
    auto it = map.begin();
    while (it != map.end()) {
        cout << "nom: " << it->first << "," <<
        "coordonnees: (" << get<1> (it->second) << ", " <<
        get<2> (it->second) << ")" << endl;
        ++it;
    }
}

array<array<int, nombreDeVilles>, nombreDeVilles> dist(map<string,tuple<int,int,int>> map){
    array<array<int, nombreDeVilles>, nombreDeVilles> v;
    for (auto it = map.begin(); it != map.end(); it++ ) {
        int id1 = get<0> (it->second);
        int x1 = get<1> (it->second);
        int y1 = get<2> (it->second);

        for (auto it2 = map.begin(); it2 != next(it); it2++ ) {
            int id2 = get<0> (it2->second);
            int x2 = get<1> (it2->second);
            int y2 = get<2> (it2->second);

            if (id1 == id2){
                v[id1][id2] = 0;
            }
            else {
                int d = static_cast<int>(hypot(x2-x1, y2-y1));
                v[id1][id2] = d;
                v[id2][id1] = d;
            }
        }
    }
    return v;
}

int calculTotalDistanceTournee(vector<string> &vecteurDeNomsDeVille, array<array<int, nombreDeVilles>, nombreDeVilles> DIST, map<string, tuple<int,int,int>> &maMapNomsVillesEtCoordonnees){
    int dist_total = 0;
    for(int i = 0; i < vecteurDeNomsDeVille.size(); i++){
        int id1 = get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[i]]);
        int id2 = (i != vecteurDeNomsDeVille.size() - 1) ? get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[i+1]]) : get<0>(maMapNomsVillesEtCoordonnees[vecteurDeNomsDeVille[0]]) ;
        dist_total += DIST[id1][id2];
    }

    return  dist_total;
}


void toutesLesPermutations(string& villes,int debut,int fin){
    if(debut==fin) cout<<villes<<endl;
    else{
        // Permutations made
        for(int i=debut;i<=fin;i++){
            // echange des deux lettres
            swap(villes[debut],villes[i]);
            // Appel Recursif
            toutesLesPermutations(villes, debut+1, fin);
            // On revient à la situation précédente
            swap(villes[debut],villes[i]);
        }
    }
}

void toutesLesPermutations_v(vector<string> villes,int debut,int fin, map<string,tuple<int,int,int>> map){

    if(debut==fin) {
        vector<string> comb;
        for (auto i : villes) {
            cout << i << " ";
            comb.push_back(i);
        }
        int longueur = calculTotalDistanceTournee(comb, dist(map), map);
        toutesLesTourneesEtLeurDistanceTotale.push_back(pair<vector<string>, int>(comb, longueur));
        cout << endl;
    }
    else{
        // Permutations made
        for(int i = debut; i<= fin; i++){
            // echange des deux lettres
            swap(villes[debut],villes[i]);
            // Appel Recursif
            toutesLesPermutations_v(villes, debut+1, fin, map);
            // On revient à la situation précédente
            swap(villes[debut],villes[i]);
        }
    }
}

bool sort_fct(pair<vector<string>,int> v1, pair<vector<string>,int> v2){
    return get<1>(v1) < get<1>(v2);
}

void smallRoute(vector<pair<vector<string>,int>> v){
    sort(v.begin(), v.end(), sort_fct);
    cout << endl << "plus petite distance :";
    int dist = get<1>(v[0]);
    for (auto trajet: v)
    {
        if (get<1>(trajet) == dist)
        {
            for (auto ville: get<0>(trajet))
            {
                cout << ville << " ";
            }
            cout << get<1>(trajet) << endl;
        }
    }
}

int main(){
    //string villes="AB";
    //string villes="ABCD";
    //string villes="ABDEF";
    //string villes="ALGORITHME";
    //vector<string> vecteurDeNomsDeVille{"Lille","Vda"};

    //toutesLesPermutations(villes,0,villes.size()-1);
    //toutesLesPermutations_v(vecteurDeNomsDeVille,0,vecteurDeNomsDeVille.size()-1);

    map<string,tuple<int,int,int>> m = ville_alea();
    aff_map(m);
    array<array<int, nombreDeVilles>, nombreDeVilles> distance = dist(m);

    //affiche map
    for(auto i = 0; i < distance.size(); i++){
        cout << "|";
        for(auto j = 0; j < distance.size(); j++){
            cout << setw(5) << left << distance[i][j];
        }
        cout << "|";
        cout << endl;
    }

    //vecteur nom villes
    vector<string> noms;
    auto it = m.begin();
    while (it != m.end()) {
        noms.push_back(it->first);
        it++;
    }

    toutesLesPermutations_v(noms, 0, noms.size() - 1, m);

    //distance
    cout << calculTotalDistanceTournee(noms,distance,m);

    smallRoute(toutesLesTourneesEtLeurDistanceTotale);

    return 0;
}


