#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

char premierLettre = 'a';
char derniereLettre = 'r';
string premierMot = "aaa";
string dernierMot = "rrr";
string mot_or = "arc";
int k = 3;

char succ(char oui){
    vector<char> vect (mot_or.begin(), mot_or.end());
    sort(vect.begin(), vect.end());
    auto pos = find(vect.begin(), vect.end(), oui);
    return *(pos + 1);
}

string suivant (string mot){
    int i = k;
    while (mot[i-1] == derniereLettre && i>= 1){
            mot[i-1] = premierLettre;
            i = i - 1;
    }
    mot[i-1] = succ(mot[i-1]);

    return mot;
}

void generateur (){
    string mot = premierMot;
    cout << mot << endl;
    do {
        mot = suivant(mot);
        cout << mot << endl;
    } while(mot != dernierMot);
}

string suivant2 (string mot2){
    int i = k;
    if (mot2[i-1] == derniereLettre){
        
    }
    mot2[i-1] = succ(mot2[i-1]);

    return mot2;
}

void generateur2 (){
    string mot = premierMot;
    do {
        do {
            cout << mot << endl;
        } while (next_permutation(mot.begin(), mot.end()));
        mot = suivant2(mot);
    } while(mot != dernierMot);
    cout << mot << endl;
}


int main() {
    generateur2();
    return 0;
}
