//
// Created by Administrateur on 19/09/2022.
//

#include "fonctions.h"



void multi(){
    int a;
    int t = 1;
    while (t) {
        cout << "entrez une valeur: " << endl;
        cin >> a;
        if (a < 1 || a > 9) cout << "la valeur doit etre entre 1 et 9" << endl;
        else t = 0;
    }
    for(int i=0; i<11; i++){
        cout << a << "*" << i <<"=" << a*i << endl;
    }
}

void multi_all(){
    for(int i =1; i<11; i++) {
        for(int j=1; j<11; j++) {
            cout << setw(5) << j * i;
        }
        cout << endl;
    }
}

void nb (){
    ofstream file;
    file.open("exo.txt");

    if(file) {
        stringstream buffer;
        string word;
        buffer << file.rdbuf();
        int count = 0;
        while (buffer >> word) {
            count++;
        }
        cout << count;
    }
}



