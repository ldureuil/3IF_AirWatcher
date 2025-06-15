/*************************************************************************
main_tests  -  description todo
                             -------------------
    début                : 12/06/2025
*************************************************************************/

// Réalisation du module <main_tests> (fichier functional_tests_main.cpp)

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
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
const double epsilon = 1e-6; // Tolérance pour la comparaison de doubles

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
int testComputeZone ( Statistics& test_stats, PointsManager& pointsManagerUser, Session& session )
// Algorithme : Crée une période donnée puis appelle la fonction de qualité de
// l'air pour calculer une moyenne sur un jeu de données très restreint,
// puis vérifie que les points sont attribués correctement.
{
    cout << "TF1: Test du comportement global de computeZone et de l'attribution de points" << endl;

    int points = pointsManagerUser.getPoints(session.getUserId());

    // Dates de début et fin du test
    time_t start;
    time_t end;

    string dateStr;

    tm tm_start = {};
    dateStr = "2019-01-30";
    istringstream ss1(dateStr);
    ss1 >> get_time(&tm_start, "%Y-%m-%d");
    start = mktime(&tm_start);

    tm tm_end = {};
    dateStr = "2019-02-02";
    istringstream ss2(dateStr);
    ss2 >> get_time(&tm_end, "%Y-%m-%d");
    end = mktime(&tm_end);

    vector<Measurement> results = test_stats.computeZone(44.0, 1.0, start, end, 25000, 0, "tests/test_data/tf1/ParticulierData.csv");

    if (!results.empty() && results.size() >= 4 &&
        abs(results[0].getValue() - 60.0) < epsilon &&
        abs(results[1].getValue() - 60.0) < epsilon &&
        abs(results[2].getValue() - 50.0) < epsilon &&
        abs(results[3].getValue() - 50.0) < epsilon)
    {
        cout << "OK : Les valeurs sont identiques à celles calculées manuellement" << endl;

        if (pointsManagerUser.getPoints(session.getUserId()) > points) {
            cout << "OK : Les points ont été attribués avec succès" << endl << endl;
            return EXIT_SUCCESS;
        } else {
            cout << "ERREUR : Les points n'ont pas été attribués" << endl << endl;
            return EXIT_FAILURE;
        }
    } else {
        cout << "ERREUR : Les valeurs reçues ne sont pas identiques à celles calculées manuellement" << endl << endl;
        return EXIT_FAILURE;
    }
} //----- fin de testComputeZone

int testAnalyzeCleaner( Statistics& test_stats )
// Algorithme : Appelle la fonction analyzeCleaner sur un jeu de données restreint.
// On compare les résultats avec les valeurs calculées à la main.
{
    cout << "TF2: Test du comportement global de analyzeCleaner" << endl;

    vector<Measurement> results = test_stats.analyzeCleaner("Cleaner0", 25000);

    if (!results.empty() && results.size() >= 4 &&
        std::abs(results[0].getValue() - (-25.0)) < epsilon &&
        std::abs(results[1].getValue() - (-25.0)) < epsilon &&
        std::abs(results[2].getValue() - 50.0) < epsilon &&
        std::abs(results[3].getValue() - 50.0) < epsilon)
    {
        cout << "OK : Les pourcentages d'amélioration sont identiques à ceux calculés manuellement" << endl << endl;
        return EXIT_SUCCESS;
    } else {
        cout << "ERREUR : Les valeurs reçues ne sont pas identiques à celles calculées manuellement" << endl << endl;
        return EXIT_FAILURE;
    }
} //----- fin de testAnalyzeCleaner

int testAnalyseFiabilite( Statistics& test_stats, AdminServices& test_adminServices )
// Algorithme : Appelle la fonction analyzeSensor sur un capteur suspect
// et vérifie que le capteur est jugé suspect. Ensuite, on appelle la fonction
// excludeSensor pour exclure le capteur et vérifier que l'exclusion a réussi.
{
    cout << "TF3: Test de l'analyse de fiabilité" << endl;

    int status = test_stats.analyzeSensor("Sensor2");

    if (!status) {
        cout << "OK : Le capteur est bien jugé suspect par analyzeCleaner." << endl;

        status = test_adminServices.excludeSensor("Sensor2", "tests/test_data/tf1/ParticulierData.csv");
        if (status) {
            cout << "OK : Le capteur a été exclu avec succès." << endl << endl;

            return EXIT_SUCCESS;
        } else {
            cout << "ERREUR : L'exclusion du capteur a échoué." << endl << endl;
            return EXIT_FAILURE;
        }
    } else {
        cout << "ERREUR : Le capteur est suspect." << endl << endl;
        return EXIT_FAILURE;
    }
} //----- fin de testAnalyseFiabilite

int testCompareSensor( Statistics& test_stats )
// Algorithme : Appelle la fonction de comparaison de capteurs sur le jeu de
// données de test et compare avec les valeurs calculées à la main
{
    cout << "TF4: Test de la comparaison de capteurs" << endl;

    // Dates de début et fin du test
    time_t start;
    time_t end;

    string dateStr;

    tm tm_start = {};
    dateStr = "2019-01-30";
    istringstream ss1(dateStr);
    ss1 >> get_time(&tm_start, "%Y-%m-%d");
    start = mktime(&tm_start);

    tm tm_end = {};
    dateStr = "2019-04-02";
    istringstream ss2(dateStr);
    ss2 >> get_time(&tm_end, "%Y-%m-%d");
    end = mktime(&tm_end);

    vector<Sensor> comparedSensors = test_stats.compareSensors("Sensor0", start, end);

    if (comparedSensors.size() >= 3 &&
        comparedSensors[0].getId() == "Sensor1" &&
        comparedSensors[1].getId() == "Sensor3" &&
        comparedSensors[2].getId() == "Sensor2")
    {
        cout << "OK : La comparaison de capteurs a réussi." << endl << endl;
        return EXIT_SUCCESS;
    } else {
        cout << "ERREUR : La comparaison de capteurs a échoué." << endl << endl;
        return EXIT_FAILURE;
    }
}

int testEvaluate( AdminServices& adminService, Statistics& full_stats )
// Algorithme : Appelle la fonction administrateur d'évaluation
// du temps de chaque algorithme
{
    cout << "TF5: Test du temps d'exécution des fonctionnalités principales";

    vector<double> results = adminService.evaluate(full_stats);
    for (auto& temps_ex : results) {
        if (temps_ex > 1000) {
            cout << "ERREUR : Temps d'exécution trop long : " << temps_ex << " ms" << endl << endl;
            return EXIT_FAILURE;
        }
    }

    cout << "OK : Tous les temps d'exécution sont raisonnables." << endl << endl;
    return EXIT_SUCCESS;
} //----- fin de testEvaluate

int testPermissions ( AdminServices& adminService )
// Algorithme : Appelle la fonction administrateur d'exclusion d'un
// capteur sans avoir le rôle requis
{
    cout << "TF6: Test des permissions d'un utilisateur" << endl;

    int execution = adminService.excludeSensor("Sensor0");

    if (!execution) {
        cout << "OK : L'exclusion d'un capteur a été refusée comme prévu." << endl << endl;
        return EXIT_SUCCESS;
    }

    cout << "ERREUR : L'exclusion a eu lieu malgré l'absence de rôle." << endl << endl;
    return EXIT_FAILURE;
} //----- fin de testPermissions

void initParticulierData( string path )
{
    ofstream fichier(path, ios::trunc); // ouverture avec effacement du contenu
    if (!fichier)
    {
        cerr << "Erreur : impossible d'ouvrir le fichier ParticulierData.csv en écriture." << endl;
        return;
    }

    fichier << "User0;0;false\n";
    fichier << "User1;0;false\n";

    fichier.close();
}

int main( )
// Algorithme : exécute tous les tests fonctionnels de l'application
{
    cout << "=== Début des tests fonctionnels ===" << endl;

    initParticulierData("tests/test_data/tf1/ParticulierData.csv");

    // Créer une session administrateur, une session utilisateur
    Session adminSession(UserType::ADMIN);
    Session userSession(UserType::PARTICULIER, "User0");

    // Initialiser AuthService avec cette session
    AuthService authServiceAdmin;
    authServiceAdmin.setCurrentSession(adminSession);

    AuthService authServiceUser;
    authServiceUser.setCurrentSession(userSession);

    // Chargement des jeux de tests fonctionnels et des données de l'application
    DataLoader test_dataLoader = DataLoader();
    vector<Sensor> *test_sensors = test_dataLoader.loadSensor("tests/test_data/tf1");
    vector<Cleaner> *test_cleaners = test_dataLoader.loadCleaner("tests/test_data/tf1");

    DataLoader full_dataLoader = DataLoader();
    vector<Sensor> *full_sensors = full_dataLoader.loadSensor("../data");
    vector<Cleaner> *full_cleaners = full_dataLoader.loadCleaner("../data");

    // Initialisation du fichier ParticulierData de test, que l'on utilisera
    // pour attribuer des points fictifs ou exclure des utilisateurs
    UserDataAccess userDataAccess = UserDataAccess();
    userDataAccess.initializeCSVFile("tests/test_data/tf1/ParticulierData.csv");
    vector<ParticulierData> particulierData = userDataAccess.loadParticulierData("tests/test_data/tf1/ParticulierData.csv");

    // Résultats de l'exécution des tests
    int tests_effectues = 0;
    int tests_reussis = 0;

    PointsManager test_pointsManager_admin = PointsManager(userDataAccess, &particulierData, test_sensors, &authServiceAdmin);
    Statistics test_stats_admin = Statistics(test_sensors, test_cleaners, &test_pointsManager_admin, &authServiceAdmin);
    AdminServices test_adminServices = AdminServices(userDataAccess, test_sensors, &authServiceAdmin);
    PointsManager test_pointsManager_user = PointsManager(userDataAccess, &particulierData, test_sensors, &authServiceUser);
    ++tests_effectues;
    tests_reussis += 1 - testComputeZone(test_stats_admin, test_pointsManager_user, userSession);

    ++tests_effectues;
    tests_reussis += 1 - testAnalyzeCleaner(test_stats_admin);

    ++tests_effectues;
    tests_reussis += 1 - testAnalyseFiabilite(test_stats_admin, test_adminServices);

    ++tests_effectues;
    tests_reussis += 1 - testCompareSensor(test_stats_admin);

    PointsManager full_pointsManager = PointsManager(userDataAccess, &particulierData, full_sensors, &authServiceAdmin);
    Statistics full_stats_admin = Statistics(full_sensors, full_cleaners, &full_pointsManager, &authServiceAdmin);
    AdminServices full_adminServices = AdminServices(userDataAccess, full_sensors, &authServiceAdmin);
    ++tests_effectues;
    tests_reussis +=  1 - testEvaluate(full_adminServices, full_stats_admin);

    AdminServices user_adminServices = AdminServices(userDataAccess, full_sensors, &authServiceUser);
    ++tests_effectues;
    tests_reussis += 1 - testPermissions(user_adminServices);

    cout << "=== Résumé des tests fonctionnels ===" << endl;
    cout << "Tests effectués : " << tests_effectues << endl;
    cout << "Tests réussis : " << tests_reussis << endl;
    cout << "Taux de réussite : " << (double) (tests_reussis * 100) / (double) tests_effectues << "%" << endl;

    cout << "=== Fin des tests fonctionnels ===" << endl;

    return 0;
} //----- Fin de runTests