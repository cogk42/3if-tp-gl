//
// Created by emman on 26/05/2020.
//

#ifndef INC_3IF_GL_TP_MESUREDAO_H
#define INC_3IF_GL_TP_MESUREDAO_H

#include <vector>
#include <ctime>
#include <sstream>
#include "../Metier/Mesure.h"
#include "../Metier/Coordonnees.h"
#include "../Metier/Type.h"
#include "../Metier/Capteur.h"
#include "CSVParser.h"


class MesureDAO {

public:
    // TODO ref pas ref ?
    MesureDAO(string filePath);

    ~MesureDAO();

    // TODO passer en static ?
    bool add(const Mesure& mesure);

    vector<Mesure> list(Capteur, Coordonnees, Type, time_t, time_t);

    void clean();

private:

    vector<Mesure> objetsRencontres;
    string path;

};


#endif //INC_3IF_GL_TP_MESUREDAO_H
