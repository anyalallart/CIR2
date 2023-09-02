//
// Created by Administrateur on 22/12/2022.
//

#ifndef BIM_SERVEUR_CLIENT_H
#define BIM_SERVEUR_CLIENT_H

#include <string>

namespace helpers
{
    class Client {
    public:
        int id;
        std::string nom;
        std::string prenom;
        std::string adresse;
        std::string numero_tel;
        std::string mail;

        Client()
        {}

        Client(int id, std::string nom, std::string prenom, std::string adresse, std::string numero_tel, std::string mail):
                id(id), nom(nom), prenom(prenom),adresse(adresse), numero_tel(numero_tel), mail(mail) {}

    };

    class Type {
    public:
        int id;
        std::string nom;
        int interet;

        Type() {};
        Type(int id, std::string nom, int interet): id(id), nom(nom), interet(interet) {}
    };

    class Compte {
    public:
        int id;
        int client;
        int type;
        float solde;

        Compte() {}
        Compte(int id, int client, int type, float solde): id(id), client(client), type(type), solde(solde) {
        }
    };
}

#endif //BIM_SERVEUR_CLIENT_H
