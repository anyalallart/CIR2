//
// Created by Administrateur on 15/11/2022.
//

#include "Compte.h"


Compte::Compte(boost::uuids::uuid client, std::string type, boost::uuids::uuid ref_banque) {
    boost::uuids::uuid uuid = boost::uuids::random_generator()();
    this->id = uuid;
    this->num_client=client;
    this->type=type;
    this->ref_banque=ref_banque;
    this->solde=0;

}


boost::uuids::uuid Compte::get_id() {
    return this->id;
}

boost::uuids::uuid Compte::get_num_client() {
    return this->num_client;
}

boost::uuids::uuid Compte::get_ref_banque()  {
    return this->ref_banque;
}

string Compte::get_type()  {
    return this->type;
}


void Compte::set_solde(int solde) {
    this->solde=solde;
}