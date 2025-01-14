//
// Created by emman on 26/05/2020.
//

#include "ServiceContributeur.h"
#include "../DAO/MesureDAO.h"
#include "../DAO/ContributeurDAO.h"

bool ServiceContributeur::envoyerDonnees(const Mesure& donnees) {

    MesureDAO dao;
    return dao.add(donnees);

}

Contributeur* ServiceContributeur::getContributeur(const string &userID) {
    ContributeurDAO contribDao;
    const auto contributeur = contribDao.getContributeur(userID);
    return contributeur;
}

vector<string*>* ServiceContributeur::listUsers() {

    ContributeurDAO dao;
    return dao.getUsernames();
}
