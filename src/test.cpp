//
// Created by emman on 26/05/2020.
//

#include <iostream>
#include <string>
#include <vector>

#include "DAO/TypeDAO.h"
#include "DAO/CapteurDAO.h"
#include "DAO/ContributeurDAO.h"
#include "Services/ServiceContributeur.h"

int main() {
    TypeDAO typeDao;

    vector<Type*> *types = typeDao.list();
    for (Type *type : *types) {
        cout << type->getAttributeId() << " / " << type->getUnite() << " / " << type->getDescription() << endl;
    }

//    CapteurDAO capteurDao;
//
//    vector<Capteur*> *capteurs = capteurDao.list();
//    for (Capteur *capteur : *capteurs) {
//        cout << capteur->getSensorId() << " / " << capteur->getCoordonnees().getLattitude() << " / " << capteur->getCoordonnees().getLongitude() << endl;
//    }

    ContributeurDAO contDao;
    Contributeur *ret = contDao.getContributeur("User0");
    cout << ret->getIdentifiant() << " / " << ret->getCapteurs()[0].getSensorId() << " / " << ret->getCapteurs()[0].getCoordonnees().getLongitude() << endl;

    cout << "test listUsers" << endl;
    for (auto truc: *ServiceContributeur::listUsers()){
        cout << (*truc) << endl;
    }
    return 0;
}