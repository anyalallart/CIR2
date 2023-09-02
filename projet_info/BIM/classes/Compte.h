//
// Created by Administrateur on 15/11/2022.
//

#ifndef BIM_COMPTE_H
#define BIM_COMPTE_H

#include <string>

#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

#include <iostream>
#include <ostream>

using namespace std;

class Compte {
private:
    boost::uuids::uuid id;
    boost::uuids::uuid num_client;
    string type;
    boost::uuids::uuid ref_banque;
    int solde;

public:
    Compte(boost::uuids::uuid client, string type, boost::uuids::uuid ref_banque);

    boost::uuids::uuid get_id();
    boost::uuids::uuid get_num_client();
    string get_type();
    boost::uuids::uuid get_ref_banque();

    void set_solde(int solde);

};


#endif //BIM_COMPTE_H
