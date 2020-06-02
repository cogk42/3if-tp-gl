
/*************************************************************************
                           Contributeur  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Contributeur> (fichier Contributeur.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

//------------------------------------------------------ Include personnel
#include "Contributeur.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

const vector<Capteur> & Contributeur::getCapteurs() const {
    return capteurs;
}

void Contributeur::setCapteurs(const vector<Capteur> &capteurs) {
    Contributeur::capteurs = capteurs;
}

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

Contributeur::Contributeur ( )
{
#ifdef MAP
    cout << "Appel au constructeur de <Contributeur>" << endl;
#endif
} //----- Fin de Contributeur

Contributeur::Contributeur(const string &identifiant, const string &motDePasse, const string &email, int points,
        int fiabilite, const vector<Capteur> &capteurs) :
    Utilisateur(identifiant, motDePasse, email),
    points(points),
    fiabilite(fiabilite),
    capteurs(capteurs)
{
#ifdef MAP
    cout << "Appel au constructeur de <Contributeur>" << endl;
#endif
} //----- Fin de Contributeur

Contributeur::~Contributeur ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Contributeur>" << endl;
#endif
} //----- Fin de ~Contributeur


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées