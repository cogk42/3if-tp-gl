//
// Created by emman on 26/05/2020.
//

#include "ServiceAnalyste.h"
#include "../DAO/MesureDAO.h"


map<Type, double> *ServiceAnalyste::agregerDonnees(const Coordonnees& centre, double rayon, time_t debut, time_t fin, bool filtrerParDistance, bool filtrerParDate)
{

    MesureDAO dao;
    vector<Mesure *> *res = dao.list(centre, rayon, debut, fin, filtrerParDistance, filtrerParDate);

    // mapper les valeurs par type
    map<Type, list<double>> valeursParType;
    for(const Mesure* mes : *res){
        // initialisation de la liste ? -> ptet pas (constr par def appelé)
        valeursParType[mes->getType()].push_back(mes->getValeur());
    }

    // mettre les moyennes dans une map par type
    map<Type, double>* moyennes = new map<Type, double>();
    for(const pair<Type, list<double>> pair : valeursParType){
        double sum = std::accumulate(std::begin(pair.second), std::end(pair.second), 0.0);
        (*moyennes)[pair.first] = sum / pair.second.size();
    }

    return moyennes;
}
