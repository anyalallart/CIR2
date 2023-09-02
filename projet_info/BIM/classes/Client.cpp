//
// Created by Administrateur on 15/11/2022.
//

#include "Client.h"

Client::Client(std::string nom, std::string prenom, std::string adresse,
               std::string numero_tel, std::string mail) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    this->numero_client = uuid;

    this->nom=nom;
    this->prenom=prenom;
    this->adresse=adresse;
    this->numero_tel=numero_tel;
    this->mail=mail;

}

boost::uuids::uuid Client::get_numero_client() {
    return this->numero_client;
}


string Client::get_nom() {
    return this->nom;
}

string Client::get_prenom() {
    return this->prenom;
};


string Client::get_adresse() {
    return this->adresse;
};

string Client::get_numero_tel() {
    return this->numero_tel;
};

string Client::get_mail() {
    return this->mail;
};

void Client::set_adresse(string adresse) {
    this->adresse=adresse;
}

void Client::set_mail(string mail) {
    this->mail=mail;
}

void Client::set_prenom(string prenom) {
    this->prenom=prenom;
}
void Client::set_nom(string nom) {
    this->nom=nom;
}
void Client::set_numero_tel(string numero_tel) {
    this->numero_tel=numero_tel;
}


