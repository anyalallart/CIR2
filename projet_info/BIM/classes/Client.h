//
// Created by Administrateur on 15/11/2022.
//

#ifndef BIM_CLIENT_H
#define BIM_CLIENT_H

#endif //BIM_CLIENT_H

#include <string>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include <iostream>
#include <ostream>

#include <map>


using namespace std;

class Client{
private:
    boost::uuids::uuid numero_client;
    string nom;
    string prenom;
    string adresse;
    string numero_tel;
    string mail;

public:

    Client(string nom,string prenom,string adresse,string numero_tel,string mail);
    boost::uuids::uuid get_numero_client();
    string get_nom();
    string get_prenom();
    string get_adresse();
    string get_numero_tel();
    string get_mail();

    void set_nom(string nom);
    void set_prenom(string prenom);
    void set_adresse(string adresse);
    void set_numero_tel(string numero_tel);
    void set_mail(string mail);




};
