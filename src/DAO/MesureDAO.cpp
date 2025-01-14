#include "MesureDAO.h"

#include <ctime>
#include <map>
#include <math.h>
#include <iomanip>
#include <sstream>

const string MesureDAO::mesurePath = "./Data/measurements.csv";
const string MesureDAO::capteurPath = "./Data/sensors.csv";
const string MesureDAO::typePath = "./Data/attributes.csv";

MesureDAO::MesureDAO() {}

bool MesureDAO::add(const Mesure& mesure) {

//    const char * formatTimestamp("%F%T");  // pas supporté on dirait -> rip
    const char * formatTimestamp("%Y-%m-%d %H:%M:%S");

    // formatTimestamp csv : timestamp;SensorID;AttributeID;Value;
    vector<string> ligne;
    stringstream ss;

    // timestamp
    time_t rawtime = mesure.getDate();
    struct tm * timeinfo;
    char buffer [200];
    timeinfo = localtime (&rawtime);

    strftime (buffer, 200, formatTimestamp, timeinfo);
//    std::cerr << "Timestamp ajouté : " << buffer << std::endl;    // debug

    ss << buffer;
    ligne.push_back(ss.str());

    // sensor ID
    ligne.push_back(mesure.getCapteur().getSensorId());

    // attribute ID
    ligne.push_back(mesure.getType().getAttributeId());

    // value
    ligne.push_back(to_string(mesure.getValeur()));

   CSVParser parser (mesurePath);
    return parser.add(ligne);

}

double distanceGPS(Coordonnees coo1, Coordonnees coo2)
{
    double lon1 = coo1.getLongitude(), lat1 = coo1.getLattitude();
    double lon2 = coo2.getLongitude(), lat2 = coo2.getLattitude();

    // https://www.movable-type.co.uk/scripts/latlong.html
    const double PI = 3.14159265359;

    // calcul distance entre deux points GPS
    const double R = 6371e3; // rayon de la Terre en mètres

    const double p1 = lat1 * PI / 180; // angles en (radians)
    const double p2 = lat2 * PI / 180;
    const double dp = (lat2 - lat1) * PI / 180;
    const double dl = (lon2 - lon1) * PI / 180;

    const double a = sin(dp / 2) * sin(dp / 2) + cos(p1) * cos(p2) * sin(dl / 2) * sin(dl / 2);
    const double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    const double d = R * c; // distance en mètres

    return d;
}

void deleteMap(map<string, vector<string*>*>* &map) {
    for (auto it = map->begin(); it != map->end(); ++it) {
        for (string *str : *it->second) {
            delete str;
        }
        delete it->second;
    }
    delete map;
}

void deleteVec(vector<vector<string*>*>* &vec) {
    for (auto inVec : *vec) {
        for (auto str : *inVec) {
            delete str;
        }
        delete inVec;
    }
    delete vec;
}

vector<Mesure *> *MesureDAO::list(Coordonnees centre, double rayon, time_t debut, time_t fin, bool filtrerParDistance, bool filtrerParDate)
{
    CSVParser parserMesure(mesurePath);
    CSVParser parserCapteur(capteurPath);
    CSVParser parserType(typePath);

    // Récupération des mesures
    vector<vector<string*>*>* mesures = parserMesure.readVec();
    map<string, vector<string*>*>* capteurs = parserCapteur.read();
    map<string, vector<string*>*>* types = parserType.read();

    vector<Mesure*>* retour = new vector<Mesure*>();

    // Tri des mesures
    for (auto line : *mesures) {
        string &dateStr = *line->at(0);
        string &nomCapteur = *line->at(1);
        string &nomType = *line->at(2);
        string &valeur = *line->at(3);


        try {
            // Récupération du capteur
            vector<string *> *capteurCsv = capteurs->at(nomCapteur);
            Capteur capteur(*(*capteurCsv)[0], "", Coordonnees(stod(*(*capteurCsv)[1]), stod(*(*capteurCsv)[2])));

            // récupération du type
            vector<string *> *typeCsv = types->at(nomType);
            Type type(*(*typeCsv)[0], *(*typeCsv)[1], *(*typeCsv)[2]);

            // Vérification de la mesure
            tm tm{};
            istringstream str_stream(dateStr);
            str_stream >> get_time(&tm, "%Y-%m-%d %T");
            time_t date = mktime(&tm);
            const bool validDate = filtrerParDate ? (debut < date && date < fin) : true;
            const bool validDistance = filtrerParDistance ? (distanceGPS(centre, capteur.getCoordonnees()) <= rayon) : true;
            const bool valid = validDate && validDistance;
            if (valid)
            {
                Mesure *mesure = new Mesure(stod(valeur), date, "", capteur, type);
                retour->push_back(mesure);
            }
        } catch (int e) {
            cerr << "Ligne intraitable : " << nomCapteur << " ou " << nomType << " introuvable." << endl;
            continue;
        }
    }

    // Nettoyage mémoire
    deleteVec(mesures);
    deleteMap(capteurs);
    deleteMap(types);

    return retour;
}

void MesureDAO::clean() {
    // TODO
}

MesureDAO::~MesureDAO() {

}

