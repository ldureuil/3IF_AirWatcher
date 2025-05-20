/*************************************************************************
CLI  -  description todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---------- Réalisation du module <CLI> (fichier CLI.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
//------------------------------------------------------ Include personnel
#include "../DataAccess/AuthDataAccess.h"
#include "../Data/Credentials.h"
#include "../Authentification/AuthService.h"
#include "../Authentification/Session.h"
#include "../Authentification/UserType.h"
#include "../DataAccess/DataLoader.h"
#include "../Services/Statistics.h"
#include "../Services/AdminServices.h"
#include "../Services/PointsManager.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void testDataLoader()
// Algorithme :
//
{
    DataLoader loader;

    // Charger les capteurs
    vector<Sensor>* sensors = loader.loadSensor("../data", UserType::USER);
    if (sensors)
    {
        cout << "Nombre de capteurs chargés : " << sensors->size() << endl;
        if(!sensors->empty())
        {
			cout << "Liste des capteurs : " << endl;
			for (auto& sensor : *sensors)
			{
            	cout << "ID : " << sensor.getId() << ", lat : " << sensor.getLat() << ", lng : " << sensor.getLng()
					 << ", userId : " << sensor.getUserId() << endl;
				cout << "Mesures : " << endl;
				for (auto& measure : sensor.getAllMeasurements())
                {
                    time_t ts = measure.getTs();
                    cout << "date : " << ctime(&ts) << ", attr_id : " << measure.getAttr_id() << ", attr_unit : "
					<< measure.getAttr_unit() << ", attr_desc : " << measure.getAttr_desc() << ", value : " << measure.getValue() << endl;
                }
				cout << endl;
			}
        }
    }
    else
    {
        cout << "Aucun capteur n'a été chargé." << endl;
    }

    // Charger les cleaners
    vector<Cleaner>* cleaners = loader.loadCleaner("../data", UserType::USER);
    if (cleaners)
    {
        cout << "Nombre de cleaners chargés : " << cleaners->size() << endl;
        if(!cleaners->empty())
        {
			cout << "Liste des cleaners : " << endl;
			for (auto& cleaner : *cleaners)
			{
				time_t start = cleaner.getStart();
				time_t end = cleaner.getEnd();

            	cout << "ID : " << cleaner.getId() << ", lat : " << cleaner.getLat() << ", lng : " << cleaner.getLng()
					 << ", start : " << ctime(&start) << ", stop : " << ctime(&end) << endl;
			}
        }
    }
    else
    {
        cout << "Aucun cleaner n'a été chargé." << endl;
    }
} //----- fin de testDataLoader


void run()
// Algorithme :
//
{
        /*
    AuthDataAccess authDataAccess = AuthDataAccess();
    vector<Credentials> authData = authDataAccess.loadCredentials();
    AuthService authService = AuthService();

    string login;
    string password;
    */

    Session session = Session();
    bool fin = false;
    /*
    bool connecte = false;
    while (!fin && !connecte)
    {

        cout << "Menu authentification :" << endl;
        cout << "1: S'authentifier" << endl;
        cout << "0: Quitter l'application" << endl;

        int choix;
        cin >> choix;

        switch(choix)
        {
            case 0:
                fin = true;
                break;
            case 1:
                cout << "Entrez votre login : ";
                cin >> login;
                cout << "Entrez votre mot de passe : ";
                cin >> password;

                session = authService.login(login, password);

                if (session.getLogin() != login)
                {
                    cout << "Identifiants incorrects, veuillez réessayer." << endl;
                }
                else
                {
                    connecte = true;
                }

                break;
            default:
                cout << "Choix incorrect, veuillez entrer un entier valide." << endl;
                break;
        }
    }
    */

    UserType userType = FOURNISSEUR; //PROVISOIRE !!!!!!! -> session.getUserType()

    DataLoader dataLoader = DataLoader();
    vector<Sensor> *sensors = dataLoader.loadSensor("../data", userType);;
    vector<Cleaner> *cleaners = dataLoader.loadCleaner("../data", userType);

    UserDataAccess userDataAccess = UserDataAccess();
    userDataAccess.initializeCSVFile("../../data/ParticulierData.csv");
    vector<ParticulierData> particulierData = userDataAccess.loadParticulierData();

    
    PointsManager pointsManager = PointsManager(userDataAccess, &particulierData, sensors);
    Statistics statistics = Statistics(sensors, cleaners, &pointsManager);
    AdminServices adminServices = AdminServices(userDataAccess, sensors);

    while (!fin)
    {
        cout << "Menu principal de l'application :" << endl;
        if (userType == FOURNISSEUR)
        {
            cout << "7: Suivre l'impact d'un cleaner" << endl;
        }
        else
        {
            cout << "1: Calculer la qualité de l'air" << endl;
            cout << "2: Comparer les capteurs" << endl;
            
            if (userType == PARTICULIER)
            {
                cout << "3: Consulter mon nombre de points" << endl;
            }
            else if (userType == ADMIN)
            {
                cout << "4: Analyser la fiabilité d'un capteur" << endl;
                cout << "5: Exclure un capteur" << endl;
                cout << "6: Mesurer les performances des algorithmes" << endl;
            }
            cout << "0: Quitter l'application" << endl;
        }

        string sensorID;
        string cleanerID;
        tm tm = {};
        time_t start;
        time_t end;
        int radius;
        int exitStatus;
        int points;
        int compteur;
        double lat;
        double lng;
        vector<Sensor> similarSensors;
        vector<Measurement> statisticsZone;
        vector<int> statisticsCleaner;

        int choix;
        cin >> choix;

        switch(choix)
        {
            case 0:
                fin = true;
                break;
            case 1: // Testé, mais n'attribue pas les points aux utilisateurs
                cout << "Entrez la latitude du centre de la zone à analyser : " << endl;
                cin >> lat;
                cout << "Entrez la longitude du centre de la zone à analyser : " << endl;
                cin >> lng;
                cout << "Entrez la date du début de la période d'analyse (format YYYY-MM-DD) : " << endl;
                cin >> get_time(&tm, "%Y-%m-%d");
                start = mktime(&tm);
                cout << "Entrez la date de la de la période d'analyse (format YYYY-MM-DD, peut être égale à celle de début) : " << endl;
                cin >> get_time(&tm, "%Y-%m-%d");
                end = mktime(&tm);
                cout << "Entrez le rayon de la zone à analyser (0 pour une estimation en un point précis) : " << endl;
                cin >> radius;

                statisticsZone = statistics.computeZone(lat, lng, start, end, radius);

                if (statisticsZone.empty())
                {
                    cout << "Les capteurs à proximité de la zone considérée et leurs mesures sur la période considérée ne nous ont pas permis de réaliser de statistiques." << endl;
                }
                else
                {
                    cout << "Voici les moyennes des mesures effectuées dans la zone considérée, pour chaque indicateur de la qualité de l'air : " << endl;
                    for (vector<Measurement>::iterator indicateur = statisticsZone.begin(); indicateur != statisticsZone.end(); indicateur++)
                    {
                        cout << indicateur->getAttr_id() << " : " << indicateur->getValue() << indicateur->getAttr_unit() << endl;
                    }
                }
                break;
            case 2: // Testé
                cout << "Entrez l'ID du capteur à comparer avec les autres : " << endl;
                cin >> sensorID;
                cout << "Entrez la date du début de la période de comparaison (format YYYY-MM-DD) : " << endl;
                cin >> get_time(&tm, "%Y-%m-%d");
                start = mktime(&tm);
                cout << "Entrez la date de la de la période de comparaison (format YYYY-MM-DD) : " << endl;
                cin >> get_time(&tm, "%Y-%m-%d");
                end = mktime(&tm);

                similarSensors = statistics.compareSensors(sensorID, start, end);

                if (similarSensors.empty())
                {
                    cout << "Il y a eu une erreur lors de la comparaison des capteurs." << endl;
                }
                else
                {
                    cout << "Voici la liste des capteurs, triée par similarité décroissante avec le capteur considéré, sur la période considérée : " << endl;
                    for (vector<Sensor>::iterator sensor = similarSensors.begin(); sensor != similarSensors.end(); sensor++)
                    {
                        cout << sensor->getId() << " : " << ++compteur << "e; ";
                    }
                }
                break;
            case 3: // Testé
                points = pointsManager.getPoints("User1"); // À remplacer par session.getUserID() quand on aura un système d'auth
                if (points == -1)
                {
                    cout << "Vous n'êtes pour l'instant pas inscrit dans la liste des particuliers ayant gagné des points." << endl;
                }
                else
                {
                    cout << "Voici votre solde de points actuel : " << points << endl;
                }
                break;
            case 4: // Testé, tlm est sus askip
                cout << "Entrez l'ID du capteur à analyser : " << endl;
                cin >> sensorID;

                exitStatus = statistics.analyzeSensor(sensorID);

                if (exitStatus == 1)
                {
                    cout << "Ce capteur a été jugé fiable sur la période considérée. Nous avons pas trouvé de gros écart avec les capteurs les plus proches." << endl;
                }
                else if (exitStatus == 0)
                {
                    cout << "Ce capteur a été jugé suspect par nos analyses, de gros écarts ont été détéctés avec ses voisins." << endl;
                }
                else
                {
                    cout << "Les mesures présentes dans la base sur la période considérée ne nous ont pas permis de trancher quant à la fiabilité du capteur en question.";
                }

                break;
            case 5: // Doesn't work yet
                cout << "Entrez l'ID du capteur dont le propriétaire doit être exclus : " << endl;
                cin >> sensorID;

                exitStatus = adminServices.excludeSensor(sensorID);
                if (exitStatus == 1)
                {
                    cout << "Ce capteur et toutes les mesures provenant de ce particulier ont été exclues des requêtes futures." << endl;
                }
                else if (exitStatus == 0)
                {
                    cout << "Ce capteur était déjà exclus de la base." << endl;
                }
                else
                {
                    cout << "L'ID renseigné ne correspond pas à un capteur de la base. L'exclusion n'a pas pu avoir lieu.";
                }

                break;
            case 6: // PAS IMPLÉMENTÉ
                cout << "Cette fonction n'a pas encore été implémentée, et nous en sommes désolés !" << endl;
                break;
            case 7: // Core dumped yay
                cout << "Entrez l'ID du cleaner à analyser : " << endl;
                cin >> cleanerID;
                cout << "Entrez le rayon souhaité : " << endl;
                cin >> radius;

                statisticsCleaner = statistics.analyzeCleaner(cleanerID, radius);

                cout << "???" << endl;

                break;
            default:
                cout << "Choix incorrect, veuillez entrer un entier valide." << endl;
                break;
        }
    }
} //----- fin de run

int main(int argc, char *argv[])
// Algorithme :
//
{
    run();
	// testDataLoader();
    return 0;
} //----- fin de main

