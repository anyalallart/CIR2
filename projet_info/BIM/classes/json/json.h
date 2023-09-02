//
// Created by Administrateur on 21/11/2022.
//

#ifndef BIM_CLIENT_JSON_H
#define BIM_CLIENT_JSON_H

#endif //BIM_CLIENT_JSON_H

#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <ostream>
#include <istream>
#include <map>

namespace pt = boost::property_tree;
using namespace std;

template <typename T>

class JSON {
    string nomfichier;

public:
    JSON(string fichier){
        this->nomfichier=fichier;
    }

    T read (string recup) {
        pt::ptree root;

        pt::read_json(this->nomfichier, root);

        T info = root.get<T>(recup, typename T);

        return (info);
    }
    void editer (string id,  string champ, T value ){
        pt::ptree root;

        root.put(id+"."+champ, value);

        pt::write_json(this->nomfichier, root);


    }

    T creer(class client ){

    }




};
