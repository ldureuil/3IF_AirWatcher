/*************************************************************************
main_tests  -  description todo
                             -------------------
    début                : 12/06/2025
*************************************************************************/

//------ Réalisation du module <main_tests> (fichier functional_tests_main.cpp) -----

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
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


int test1 ( Statistics test_stats, double lat, double lng, time_t start, time_t end, int radius)
// Algorithme : Crée une période donnée puis appelle la fonction de qualité de
// l'air pour calculer une moyenne
{
    vector<Measurement> results = test_stats.computeZone(lat, lng, start, end, radius);
    // Vérifier si le vecteur contient suffisamment d'éléments avant d'y accéder
    if (!results.empty() && results.size() > 2) {
        cout << results[0].getValue() << " " << results[2].getValue() << endl;
        return EXIT_SUCCESS;
    } else {
        cerr << "Aucun résultat ou données insuffisantes" << endl;
        return EXIT_FAILURE;
    }
} //----- fin de test1


int test5 ( AdminServices adminService, Statistics full_stats )
// Algorithme : Appelle la fonction administrateur d'évaluation
// du temps de chaque algorithme
{
    vector<double> results = adminService.evaluate( full_stats );
    for (auto& temps_ex : results) {
        if (temps_ex > 1000) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
} //----- fin de test5


int test6 ( AdminServices adminService )
// Algorithme : Appelle la fonction administrateur d'exclusion d'un
// capteur sans avoir le rôle requis
{
    int execution = adminService.excludeSensor("FakeSensorID");

    if (execution == -1) {
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
} //----- fin de test6


int main ( )
// Algorithme :
//
{
    AuthService authService = AuthService();

    authService.setCurrentSession(UserType::ADMIN);

    DataLoader dataLoader = DataLoader();
    vector<Sensor> *sensors = dataLoader.loadSensor("tests/test_data", ADMIN);
    vector<Cleaner> *cleaners = dataLoader.loadCleaner("tests/test_data", ADMIN);

    UserDataAccess userDataAccess = UserDataAccess();
    userDataAccess.initializeCSVFile("tests/test_data/ParticulierData.csv");
    vector<ParticulierData> particulierData = userDataAccess.loadParticulierData();
    
    PointsManager pointsManager = PointsManager(userDataAccess, &particulierData, sensors, &authService);
    AdminServices adminServices = AdminServices(userDataAccess, sensors, &authService);
    Statistics stats = Statistics(sensors, cleaners, &pointsManager, &authService);

    time_t start;
    time_t end;

    std::string dateStr;

    std::tm tm_start = {};
    dateStr = "2019-01-03";
    std::istringstream ss1(dateStr);
    ss1 >> std::get_time(&tm_start, "%Y-%m-%d");
    start = mktime(&tm_start);

    std::tm tm_end = {};
    dateStr = "2019-05-25";
    std::istringstream ss2(dateStr);
    ss2 >> std::get_time(&tm_end, "%Y-%m-%d");
    end = mktime(&tm_end);

    // Déclaration des timestamps
    std::chrono::high_resolution_clock::time_point t1, t2;

    // Vecteur des résultats de l'exécution
    std::vector<double> results;


    int ok = test1(stats, 43.9600415, 4.3593173, start, end, 50000);

    return 0;
} //----- fin de Nom

