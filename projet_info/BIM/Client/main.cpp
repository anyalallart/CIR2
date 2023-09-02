//
// Created by Administrateur on 21/11/2022.
//
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <map>

namespace pt = boost::property_tree;
using namespace std;


int main(){

    pt::ptree root;
    pt::ptree matrix_node;

    std::map<std::string, std::map<std::string, std::string>> m2 {{"40", {{"nom", "Langer"}, {"prenom", "Camille"}}}, {"50", {{"nom", "Lallart"}, {"prenom", "Anya"}}}};

    std::map<std::string, string> m{{"id", "40"}, {"nom", "camille"}, {"prenom", "cam"}};

    root.put(m.begin()->first,m.begin()->second);


    for (std::map<std::string,string>::iterator it=m.begin(); it!=m.end(); ++it)
        matrix_node.put(it->first,it->second);

    root.add_child("matrix", matrix_node);

    pt::write_json("user.json", root);



};
