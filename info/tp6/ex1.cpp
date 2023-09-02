//
// Created by Administrateur on 07/11/2022.
//

#include "ex1.h"

void ex1(){
    int a[]={7,4,9,1,3,4,8,2,7,5,3,6,10,4,8,10,1,2};
    std::multiset<int> s(&a[0],&a[17]);
    std::multiset<int>::iterator p=s.begin(); //tri les valeurs
    while(p!=s.end()) std::cout<<*p++<<" "; //affiche les valeurs


    std::set<int> s2(&a[0],&a[17]);
    std::set<int>::iterator p2=s2.begin(); //tri les valeurs
    while(p2!=s2.end()) std::cout<<*p2++<<" "; //affiche les valeurs

}