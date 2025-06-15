/*************************************************************************
CLI  -  interface utilisateur en ligne de commande de l'application AirWatcher
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
const int RAYON = 60000;

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void run()
// Algorithme :
//
{
    // Initialisation des services et de l'authentification
    cout << "Bienvenue dans l'application AirWatcher !" << endl;
    AuthDataAccess authDataAccess = AuthDataAccess();
    //vector<Credentials> authData = authDataAccess.loadCredentials();
    AuthService authService = AuthService();

    string credentialsFilePath = "../data/credentials.csv";
    string login;
    string password;

    Session session = Session();
    bool fin = false;
    bool connecte = false;

    while (!fin && !connecte)
    {

        cout << endl << "Menu authentification :" << endl;
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

                session = authService.login(credentialsFilePath, login, password);

                if (session.getUserType() == UserType::UNDEFINED)
                // Identifiants invalides
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
    

    UserType userType = session.getUserType();

    DataLoader dataLoader = DataLoader();
    vector<Sensor> *sensors = dataLoader.loadSensor("../data");
    vector<Cleaner> *cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess userDataAccess = UserDataAccess();
    userDataAccess.initializeCSVFile("../../data/ParticulierData.csv");
    vector<ParticulierData> particulierData = userDataAccess.loadParticulierData("../data/ParticulierData.csv");
    
    PointsManager pointsManager = PointsManager(userDataAccess, &particulierData, sensors, &authService);
    Statistics statistics = Statistics(sensors, cleaners, &pointsManager, &authService);
    AdminServices adminServices = AdminServices(userDataAccess, sensors, &authService);

    while (!fin)
    {
        cout << endl << "Menu principal de l'application :" << endl;
        if (userType == FOURNISSEUR)
        {
            cout << "C: Suivre l'impact d'un cleaner" << endl;
        }
        else
        {
            cout << "Q: Calculer la qualité de l'air" << endl;
            cout << "R: Comparer les capteurs" << endl;
            
            if (userType == PARTICULIER)
            {
                cout << "P: Consulter mon nombre de points" << endl;
            }
            else if (userType == ADMIN)
            {
                cout << "S: Analyser la fiabilité d'un capteur" << endl;
                cout << "E: Exclure un capteur" << endl;
                cout << "M: Mesurer les performances des algorithmes" << endl;
            }
        }
        cout << "X: Quitter l'application" << endl;

        string sensorID;
        string cleanerID;
        tm tm = {};
        time_t start;
        time_t end;
        int radius;
        int exitStatus;
        int points;
        double lat;
        double lng;
        vector<Sensor> similarSensors;
        vector<Measurement> statisticsZone;
        vector<Measurement> statisticsCleaner;

        char choix;
        cin >> choix;

        switch(choix)
        {
            case 'X':
                fin = true;
                break;
            case 'Q':
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
                cout << "Entrez le rayon de la zone à analyser, en km (0 pour une estimation en un point précis) : " << endl;
                cin >> radius;
                radius *= 1000;

                statisticsZone = statistics.computeZone(lat, lng, start, end, radius, 0, "../data/ParticulierData.csv");

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
            case 'R':
                cout << "Entrez l'ID du capteur à comparer avec les autres : " << endl;
                cin >> sensorID;
                cout << "Entrez la date du début de la période de comparaison (format YYYY-MM-DD) : " << endl;
                cin >> get_time(&tm, "%Y-%m-%d");
                start = mktime(&tm);
                cout << "Entrez la date de la de la période de comparaison (format YYYY-MM-DD) : " << endl;
                cin >> get_time(&tm, "%Y-%m-%d");
                end = mktime(&tm);

                similarSensors = statistics.compareSensors(sensorID, start, end);

                if (!similarSensors.empty())
                {
                    cout << "Voici la liste des capteurs, triée par similarité décroissante avec le capteur considéré, sur la période considérée : " << endl;

                    vector<Sensor>::iterator sensor = similarSensors.begin();
                    for (int i = 1; i <= 10; i++)
                    {
                        cout << sensor->getId() << " : " << i << "e; ";
                        ++sensor;
                    }
                    cout << endl;
                }

                break;
            case 'P':
                points = pointsManager.getPoints(session.getUserId());
                if (points == -1)
                {
                    cout << "Vous n'êtes pour l'instant pas inscrit dans la liste des particuliers ayant gagné des points." << endl;
                }
                else
                {
                    cout << "Voici votre solde de points actuel : " << points << endl;
                }

                break;
            case 'S':
                cout << "Entrez l'ID du capteur à analyser : " << endl;
                cin >> sensorID;

                exitStatus = statistics.analyzeSensor(sensorID);

                if (exitStatus == 1)
                {
                    cout << "Ce capteur a été jugé fiable sur la période considérée. Nous n'avons pas trouvé de gros écart avec les capteurs les plus proches." << endl;
                }
                else if (exitStatus == 0)
                {
                    cout << "Ce capteur a été jugé suspect par nos analyses, de gros écarts ont été détéctés avec ses voisins." << endl;
                }

                break;
            case 'E':
                cout << "Entrez l'ID du capteur dont le propriétaire doit être exclus : " << endl;
                cin >> sensorID;

                exitStatus = adminServices.excludeSensor(sensorID);
                if (exitStatus)
                {
                    cout << "Ce capteur et toutes les mesures provenant de ce particulier ont été exclues des requêtes futures." << endl;
                }

                break;
            case 'M':
		        adminServices.evaluate(statistics);
                break;
            case 'C':
                cout << "Entrez l'ID du cleaner à analyser : " << endl;
                cin >> cleanerID;

                statisticsCleaner = vector<Measurement>();
                statisticsCleaner = statistics.analyzeCleaner(cleanerID, RAYON);

                if (!statisticsCleaner.empty())
                {
                    cout << "Voici les pourcentages d'amélioration de chaque indicateur de la qualité de l'air grâce au cleaner : " << endl;
                    for (vector<Measurement>::iterator indicateur = statisticsCleaner.begin(); indicateur != statisticsCleaner.end(); indicateur++)
                    {
                        cout << indicateur->getAttr_id() << " : " << indicateur->getValue() << "%" << endl;
                    }
                }

                break;
            default:
                cout << "Choix incorrect, veuillez entrer une majuscule valide." << endl;
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

