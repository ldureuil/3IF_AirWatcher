/*************************************************************************
services_tests  -  tests unitaires des méthodes de la couche services
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <services_tests> (fichier services_tests.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "services_tests.h"
#include "../../Authentification/AuthService.h"
#include "../../Authentification/Session.h"
#include "../../Services/Statistics.h"
#include "../../Services/PointsManager.h"
#include "../../Services/AdminServices.h"
#include "../../DataAccess/DataLoader.h"
#include "../../DataAccess/UserDataAccess.h"
#include "../../Data/ParticulierData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int services_tests::runTests( )
// Algorithme : exécute les tests unitaires pour la couche Services
{
    cout << "=== Début des tests unitaires pour Services ===" << endl;

    int nbTestsOk = 0;

    // Tests pour Statistics::analyzeSensor
    nbTestsOk += testAnalyzeSensorInexistant(); // T1
    nbTestsOk += testAnalyzeSensorSansMesure(); // T2
    nbTestsOk += testAnalyzeSensorAnormal(); // T3
    nbTestsOk += testAnalyzeSensorNormal(); // T4

    // Tests pour Statistics::computeZone
    nbTestsOk += testComputeZoneAucunCapteur(); // T5
    nbTestsOk += testComputeZoneSansMesures(); // T6
    nbTestsOk += testComputeZoneEstimationPonctuelle(); // T7
    nbTestsOk += testComputeZoneAvecCapteurs(); // T8

    // Tests pour Statistics::analyzeCleaner
    nbTestsOk += testAnalyzeCleanerInconnu(); // T9
    nbTestsOk += testAnalyzeCleanerSansCapteurs(); // T10
    nbTestsOk += testAnalyzeCleanerValide(); // T11

    // Tests pour Statistics::compareSensors
    nbTestsOk += testCompareSensorsInexistant(); // T12
    nbTestsOk += testCompareSensorsAucunCapteur(); // T13
    nbTestsOk += testCompareSensorsValide(); // T14

    // Tests pour Statistics::extrapolateAQI
    nbTestsOk += testExtrapolateAQISansMesures(); // T15
    nbTestsOk += testExtrapolateAQIValide(); // T16

    // Tests pour PointsManager::award
    nbTestsOk += testAwardListeVide(); // T17
    /*nbTestsOk += testAwardCapteurUnique(); // T18
    nbTestsOk += testAwardDeuxCapteursUtilisateurs(); // T19
    nbTestsOk += testAwardDeuxCapteursMemUtilisateur(); // T20
    nbTestsOk += testAwardCapteurInconnu(); // T21
    nbTestsOk += testAwardCapteurExclu(); // T22
    nbTestsOk += testAwardCapteursValidesEtExclus(); // T23
    nbTestsOk += testAwardCapteurSansUtilisateur(); // T24
    nbTestsOk += testAwardCapteursValidesEtSansUtilisateur(); // T25*/

    // Tests pour PointsManager::getPoints
    nbTestsOk += testGetPointsUtilisateurInexistant(); // T26
    nbTestsOk += testGetPointsUtilisateurExistant(); // T27

    // Tests pour AdminServices::excludeSensor
    nbTestsOk += testExcludeSensorInexistant(); // T28
    nbTestsOk += testExcludeSensorDejaExclu(); // T29
    nbTestsOk += testExcludeSensorValide(); // T30

    // Tests pour AuthService::login
    nbTestsOk += testLoginCombiValide(); // T31
    nbTestsOk += testLoginCombiInvalide(); // T32

    // Tests pour AuthService::checkRequiredRole
    nbTestsOk += testCheckRequiredRolePrivilegeSuperieur(); // T33
    nbTestsOk += testCheckRequiredRolePrivilegeInferieur(); // T34

    cout << "=== Fin des tests unitaires pour Services ===" << endl;

    return nbTestsOk;
} //----- Fin de runTests

bool services_tests::testAnalyzeSensorInexistant()
// Algorithme : teste la méthode analyzeSensor avec un capteur inexistant
{
    cout << "T1: Test analyzeSensor avec un capteur inexistant" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Test
    int result = stats.analyzeSensor("Sensor999");

    // Vérification
    if (result == -1) {
        cout << "  OK: Le capteur inexistant retourne -1" << endl;
        return true;
    } else {
        cout << "  ERREUR: Résultat inattendu: " << result << " (attendu: -1)" << endl;
        return false;
    }
} //----- Fin de testAnalyzeSensorInexistant

bool services_tests::testAnalyzeSensorSansMesure()
// Algorithme : teste la méthode analyzeSensor avec un capteur sans mesures
{
    cout << "T2: Test analyzeSensor avec un capteur sans mesures" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("tests/test_data/t2");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Test
    string SensorSansMesure = "Sensor99";
    int result = stats.analyzeSensor(SensorSansMesure);

    // Vérification
    if (result == -1) {
        cout << "  OK: Le capteur sans mesures retourne -1" << endl;
        return true;
    } else {
        cout << "  ERREUR: Résultat inattendu: " << result << " (attendu: -1)" << endl;
        return false;
    }
} //----- Fin de testAnalyzeSensorSansMesure

bool services_tests::testAnalyzeSensorAnormal()
// Algorithme : Teste la méthode analyzeSensor avec un capteur ayant des valeurs anormales
{
    cout << "T3: Test de analyzeSensor avec un capteur ayant des valeurs anormales" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("tests/test_data/t3");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Test avec un capteur ayant des mesures anormales
    int result = stats.analyzeSensor("Sensor666");

    // Vérification
    if (result == 0) {
        cout << "  OK: Le capteur anormal est bien détecté comme suspect" << endl;
        return true;
    } else {
        cout << "  ERREUR: Le capteur anormal n'est pas détecté comme suspect (résultat=" << result << ")" << endl;
        return false;
    }
} //----- Fin de testAnalyzeSensorAnormal

bool services_tests::testAnalyzeSensorNormal()
// Algorithme : Teste la méthode analyzeSensor avec un capteur ayant des valeurs normales
{
    cout << "T4: Test de analyzeSensor avec un capteur ayant des valeurs normales" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Test avec un capteur ayant des mesures normales
    int result = stats.analyzeSensor("Sensor0");

    // Vérification
    if (result == 1) {
        cout << "  OK: Le capteur normal est bien détecté comme fiable" << endl;
        return true;
    } else {
        cout << "  ERREUR: Le capteur normal n'est pas détecté comme fiable (résultat=" << result << ")" << endl;
        return false;
    }
} //----- Fin de testAnalyzeSensorNormal

bool services_tests::testComputeZoneAucunCapteur()
// Algorithme : Teste la méthode computeZone dans une zone sans capteurs
{
    cout << "T5: Test de computeZone dans une zone sans capteurs" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Coordonnées d'une zone sans capteurs à proximité
    double lat = 48.0;
    double lng = 5.0;

    // Période de test
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 10;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 10;
    tm_end.tm_mday = 2;
    time_t end = mktime(&tm_end);

    // Test avec un rayon de 10km
    vector<Measurement> result = stats.computeZone(lat, lng, start, end, 10);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucune mesure trouvée dans une zone sans capteurs" << endl;
        return true;
    } else {
        cout << "  ERREUR: Des mesures ont été trouvées dans une zone sans capteurs" << endl;
        return false;
    }
} //----- Fin de testComputeZoneAucunCapteur

bool services_tests::testComputeZoneSansMesures()
// Algorithme : Teste la méthode computeZone dans une zone avec des capteurs mais sans mesures
{
    cout << "T6: Test de computeZone dans une zone avec capteurs mais sans mesures" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Coordonnées d'une zone avec capteurs
    double lat = 44;
    double lng = -1;

    // Période sans mesures (date future)
    struct tm tm_start = {};
    tm_start.tm_year = 2100 - 1900;
    tm_start.tm_mon = 10;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2100 - 1900;
    tm_end.tm_mon = 10;
    tm_end.tm_mday = 2;
    time_t end = mktime(&tm_end);

    // Test avec un rayon de 10km
    vector<Measurement> result = stats.computeZone(lat, lng, start, end, 10000);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucune mesure trouvée dans la période spécifiée" << endl;
        return true;
    } else {
        cout << "  ERREUR: Des mesures ont été trouvées pour une période sans données" << endl;
        return false;
    }
} //----- Fin de testComputeZoneSansMesures

bool services_tests::testComputeZoneEstimationPonctuelle()
// Algorithme : Teste la méthode computeZone avec un rayon de 0 (estimation ponctuelle)
{
    cout << "T7: Test de computeZone avec un rayon de 0 (estimation ponctuelle)" << endl;

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Coordonnées proches de capteurs connus
    double lat = 44;
    double lng = 4.0;

    // Période avec mesures
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 1;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 1;
    tm_end.tm_mday = 1;
    time_t end = mktime(&tm_end);

    // Test avec un rayon de 0 (estimation ponctuelle)
    vector<Measurement> result = stats.computeZone(lat, lng, start, end, 0, 10000);

    // Vérification
    if (!result.empty()) {
        cout << "  OK: Estimation ponctuelle réussie avec " << result.size() << " mesures" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucune mesure trouvée pour l'estimation ponctuelle" << endl;
        return false;
    }
} //----- Fin de testComputeZoneEstimationPonctuelle

bool services_tests::testComputeZoneAvecCapteurs()
// Algorithme : Teste la méthode computeZone dans une zone avec des capteurs et des mesures
{
    cout << "T8: Test de computeZone dans une zone avec capteurs et mesures" << endl;

    Session session(UserType::USER);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Coordonnées d'une zone avec capteurs
    double lat = 44.0;
    double lng = 4.0;

    // Période avec mesures
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 1;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 1;
    tm_end.tm_mday = 10;
    time_t end = mktime(&tm_end);

    // Test avec un rayon de 10km
    vector<Measurement> result = stats.computeZone(lat, lng, start, end, 10000);

    // Vérification
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " mesures trouvées dans la zone avec capteurs" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucune mesure trouvée dans une zone qui devrait en contenir" << endl;
        return false;
    }
} //----- Fin de testComputeZoneAvecCapteurs

bool services_tests::testAnalyzeCleanerInconnu()
// Algorithme : teste la méthode analyzeCleaner avec un cleaner inexistant
{
    cout << "T9: Test de analyzeCleaner avec un cleaner inexistant" << endl;

    Session session(UserType::FOURNISSEUR);
    AuthService authService;
    authService.setCurrentSession(session);
    
    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");
    
    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");
    
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);
    
    // Test avec un cleaner inexistant
    vector<Measurement> result = stats.analyzeCleaner("Cleaner5");
    
    // Vérification
    if (result.empty()) {
        cout << "  OK: Un vecteur vide est retourné pour un cleaner inexistant" << endl;
        return true;
    } else {
        cout << "  ERREUR: Un vecteur non vide est retourné pour un cleaner inexistant" << endl;
        return false;
    }
} //----- Fin de testAnalyzeCleanerInconnu

bool services_tests::testAnalyzeCleanerSansCapteurs()
// Algorithme : teste la méthode analyzeCleaner avec un cleaner n'ayant pas de capteurs à proximité
{
    cout << "T10: Test de analyzeCleaner avec un cleaner sans capteurs à proximité" << endl;

    Session session(UserType::FOURNISSEUR);
    AuthService authService;
    authService.setCurrentSession(session);

    // Implémentez ici les tests unitaires pour les méthodes de la couche Data
    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");
    
    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");
    
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);
    
    // Test avec un cleaner sans capteurs à proximité
    vector<Measurement> result = stats.analyzeCleaner("Cleaner0", 100); // Rayon très petit
    
    // Vérification
    if (result.empty()) {
        cout << "  OK: Un vecteur vide est retourné pour un cleaner sans capteurs à proximité" << endl;
        return true;
    } else {
        cout << "  ERREUR: Un vecteur non vide est retourné pour un cleaner sans capteurs à proximité" << endl;
        return false;
    }
} //----- Fin de testAnalyzeCleanerSansCapteurs

bool services_tests::testAnalyzeCleanerValide()
// Algorithme : teste la méthode analyzeCleaner avec un cleaner valide ayant des capteurs à proximité
{
    cout << "T11: Test de analyzeCleaner avec un cleaner valide" << endl;

    Session session(UserType::FOURNISSEUR);
    AuthService authService;
    authService.setCurrentSession(session);
    
    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");
    
    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");
    
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);
    
    // Test avec un cleaner valide et des capteurs à proximité
    vector<Measurement> result = stats.analyzeCleaner("Cleaner0", 100000);
    
    // Vérification
    if (!result.empty()) {
        cout << "  OK: Un vecteur de " << result.size() << " mesures est retourné pour un cleaner valide" << endl;
        return true;
    } else {
        cout << "  ERREUR: Un vecteur vide est retourné pour un cleaner valide avec capteurs" << endl;
        return false;
    }
} //----- Fin de testAnalyzeCleanerValide

bool services_tests::testCompareSensorsInexistant()
// Algorithme : teste la méthode compareSensors avec un capteur inexistant
{
    cout << "T12: Test de compareSensors avec un capteur inexistant" << endl;

    Session session(UserType::USER);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Définition de la période de test
    time_t start, end;
    struct tm tm_start = {}, tm_end = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 1;
    tm_start.tm_mday = 1;
    start = mktime(&tm_start);

    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 1;
    tm_end.tm_mday = 31;
    end = mktime(&tm_end);

    // Test avec un capteur inexistant
    vector<Sensor> result = stats.compareSensors("Sensor100", start, end);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucun capteur similaire trouvé pour un capteur inexistant" << endl;
        return true;
    } else {
        cout << "  ERREUR: Un vecteur non vide est retourné pour un capteur inexistant" << endl;
        return false;
    }
} //----- Fin de testCompareSensorsInexistant

bool services_tests::testCompareSensorsAucunCapteur()
// Algorithme : teste la méthode compareSensors avec un capteur valide mais sans autres capteurs disponibles pour la comparaison
{
    cout << "T13: Test de compareSensors sans capteurs pour la comparaison" << endl;

    Session session(UserType::USER);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("tests/test_data/t13");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Définition de la période de test
    time_t start, end;
    struct tm tm_start = {}, tm_end = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 1;
    tm_start.tm_mday = 1;
    start = mktime(&tm_start);

    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 1;
    tm_end.tm_mday = 31;
    end = mktime(&tm_end);

    // Test avec un capteur valide mais sans autres capteurs pour la comparaison (les autres n'ont pas de mesures dans la période)
    vector<Sensor> result = stats.compareSensors("Sensor0", start, end);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucun capteur similaire trouvé quand il n'y a pas d'autres capteurs disponibles" << endl;
        return true;
    } else {
        cout << "  ERREUR: Un vecteur non vide est retourné alors qu'il ne devrait pas y avoir de capteurs similaires" << endl;
        return false;
    }
} //----- Fin de testCompareSensorsAucunCapteur

bool services_tests::testCompareSensorsValide()
// Algorithme : teste la méthode compareSensors avec un capteur valide et d'autres capteurs disponibles pour la comparaison
{
    cout << "T14: Test de compareSensors avec des capteurs valides" << endl;

    Session session(UserType::USER);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Définition de la période de test
    time_t start, end;
    struct tm tm_start = {}, tm_end = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 1;
    tm_start.tm_mday = 1;
    start = mktime(&tm_start);

    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 1;
    tm_end.tm_mday = 31;
    end = mktime(&tm_end);

    // Test avec un capteur valide et d'autres capteurs disponibles
    vector<Sensor> result = stats.compareSensors("Sensor0", start, end);

    // Vérification
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " capteurs similaires trouvés" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucun capteur similaire trouvé alors que des capteurs sont disponibles" << endl;
        return false;
    }
} //----- Fin de testCompareSensorsValide

bool services_tests::testExtrapolateAQISansMesures()
// Algorithme : teste la méthode extrapolateAQI avec des coordonnées où aucune mesure n'est disponible
{
    cout << "T15: Test de extrapolateAQI sans mesures disponibles" << endl;

    Session session(UserType::USER);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Définition de la période de test
    time_t start, end;
    struct tm tm_start = {}, tm_end = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 1;
    tm_start.tm_mday = 1;
    start = mktime(&tm_start);

    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 1;
    tm_end.tm_mday = 1;
    end = mktime(&tm_end);

    // Test avec des coordonnées où aucun capteur n'est présent
    double lat = 60.0;
    double lng = 10.0;
    int radiusExtrapolation = 1000; // 1km de rayon d'extrapolation

    vector<Measurement> result = stats.extrapolateAQI(lat, lng, start, end, radiusExtrapolation);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucune mesure extrapolée comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: Des mesures ont été extrapolées alors qu'aucun capteur n'est disponible" << endl;
        return false;
    }
} //----- Fin de testExtrapolateAQISansMesures

bool services_tests::testExtrapolateAQIValide()
// Algorithme : teste la méthode extrapolateAQI avec des coordonnées valides et des capteurs à proximité
{
    cout << "T16: Test de extrapolateAQI avec des capteurs à proximité" << endl;

    Session session(UserType::USER);
    AuthService authService;
    authService.setCurrentSession(session);

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);
    Statistics stats(sensors, cleaners, &pointsManager, &authService);

    // Définition de la période de test
    time_t start, end;
    struct tm tm_start = {}, tm_end = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 11;
    tm_start.tm_mday = 25;
    start = mktime(&tm_start);

    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 11;
    tm_end.tm_mday = 31;
    end = mktime(&tm_end);

    // Test avec des coordonnées proches des capteurs
    double lat = 44.0;
    double lng = 4.0;
    int radiusExtrapolation = 10000;

    vector<Measurement> result = stats.extrapolateAQI(lat, lng, start, end, radiusExtrapolation);

    // Vérification
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " mesures extrapolées" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucune mesure extrapolée alors que des capteurs sont disponibles" << endl;
        return false;
    }
} //----- Fin de testExtrapolateAQIValide

bool services_tests::testAwardListeVide()
// Algorithme : teste la méthode award avec une liste vide de capteurs
{
    cout << "T17: Test de award avec une liste vide de capteurs" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec une liste vide de capteurs
    vector<string> emptySensorsList;
    bool result = pointsManager.award(emptySensorsList);

    // Vérification que la méthode renvoie true même avec une liste vide
    if (result) {
        cout << "  OK: award a correctement traité une liste vide" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité une liste vide" << endl;
        return false;
    }
} //----- Fin de testAwardListeVide

bool services_tests::testAwardCapteurUnique()
// Algorithme : teste la méthode award avec un seul capteur valide
{
    cout << "T18: Test de award avec un capteur unique" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un capteur unique
    vector<string> sensorsList = {"Sensor36"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true pour un capteur valide
    if (result) {
        cout << "  OK: award a correctement traité un capteur unique valide" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité un capteur unique valide" << endl;
        return false;
    }
} //----- Fin de testAwardCapteurUnique

bool services_tests::testAwardDeuxCapteursUtilisateurs()
// Algorithme : teste la méthode award avec deux capteurs appartenant à des utilisateurs différents
{
    cout << "T19: Test de award avec deux capteurs de différents utilisateurs" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec deux capteurs de différents utilisateurs
    vector<string> sensorsList = {"Sensor70", "Sensor36"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true et que les deux utilisateurs reçoivent des points
    if (result) {
        cout << "  OK: award a correctement traité deux capteurs de différents utilisateurs" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité deux capteurs de différents utilisateurs" << endl;
        return false;
    }
} //----- Fin de testAwardDeuxCapteursUtilisateurs

bool services_tests::testAwardDeuxCapteursMemUtilisateur()
// Algorithme : teste la méthode award avec deux capteurs appartenant au même utilisateur
{
    cout << "T20: Test de award avec deux capteurs du même utilisateur" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec deux capteurs du même utilisateur
    vector<string> sensorsList = {"Sensor36", "Sensor36"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true et que l'utilisateur ne reçoit des points qu'une seule fois
    if (result) {
        cout << "  OK: award a correctement traité deux capteurs du même utilisateur" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité deux capteurs du même utilisateur" << endl;
        return false;
    }
} //----- Fin de testAwardDeuxCapteursMemUtilisateur

bool services_tests::testAwardCapteurInconnu()
// Algorithme : teste la méthode award avec un capteur inconnu
{
    cout << "T21: Test de award avec un capteur inconnu" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un capteur inconnu
    vector<string> sensorsList = {"Sensor100"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie false pour un capteur inconnu
    if (!result) {
        cout << "  OK: award a correctement identifié un capteur inconnu" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement identifié un capteur inconnu" << endl;
        return false;
    }
} //----- Fin de testAwardCapteurInconnu

bool services_tests::testAwardCapteurExclu()
// Algorithme : teste la méthode award avec un capteur dont l'utilisateur est exclu
{
    cout << "T22: Test de award avec un capteur exclu" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un capteur dont l'utilisateur est exclu
    vector<string> sensorsList = {"Sensor70"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true mais n'attribue pas de points
    if (result) {
        cout << "  OK: award a correctement traité un capteur d'un utilisateur exclu" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité un capteur d'un utilisateur exclu" << endl;
        return false;
    }
} //----- Fin de testAwardCapteurExclu

bool services_tests::testAwardCapteursValidesEtExclus()
// Algorithme : teste la méthode award avec un mélange de capteurs valides et exclus
{
    cout << "T23: Test de award avec capteurs valides et exclus" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un mélange de capteurs valides et excluscapteur_inexistant
    vector<string> sensorsList = {"Sensor70", "Sensor36"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true et attribue des points seulement aux utilisateurs non exclus
    if (result) {
        cout << "  OK: award a correctement traité un mélange de capteurs valides et exclus" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité un mélange de capteurs valides et exclus" << endl;
        return false;
    }
} //----- Fin de testAwardCapteursValidesEtExclus

bool services_tests::testAwardCapteurSansUtilisateur()
// Algorithme : teste la méthode award avec un capteur sans utilisateur associé
{
    cout << "T24: Test de award avec un capteur sans utilisateur" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Initialisation des services
    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un capteur sans utilisateur
    vector<string> sensorsList = {"Sensor45"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true mais n'attribue pas de points
    if (result) {
        cout << "  OK: award a correctement traité un capteur sans utilisateur" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité un capteur sans utilisateur" << endl;
        return false;
    }
} //----- Fin de testAwardCapteurSansUtilisateur

bool services_tests::testAwardCapteursValidesEtSansUtilisateur()
// Algorithme : teste la méthode award avec un mélange de capteurs valides et sans utilisateur
{
    cout << "T25: Test de award avec capteurs valides et sans utilisateur" << endl;

    // Chargement des données de test
    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Initialisation des services
    UserDataAccess uda;
    AuthService authService;
    vector<ParticulierData> particulierData;

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un mélange de capteurs valides et sans utilisateur
    vector<string> sensorsList = {"Sensor43", "Sensor36"};
    bool result = pointsManager.award(sensorsList);

    // Vérification que la méthode renvoie true et attribue des points seulement aux capteurs avec utilisateur
    if (result) {
        cout << "  OK: award a correctement traité un mélange de capteurs valides et sans utilisateur" << endl;
        return true;
    } else {
        cout << "  ÉCHEC: award n'a pas correctement traité un mélange de capteurs valides et sans utilisateur" << endl;
        return false;
    }
} //----- Fin de testAwardCapteursValidesEtSansUtilisateur

bool services_tests::testGetPointsUtilisateurInexistant()
// Algorithme : teste la méthode getPoints avec un utilisateur qui n'existe pas
{
    cout << "T26: Test de getPoints avec un utilisateur inexistant" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    Session session(UserType::PARTICULIER, "user10");
    AuthService authService;
    authService.setCurrentSession(session);
    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec un utilisateur inexistant
    string userId = "User10";
    int points = pointsManager.getPoints(userId);

    // Vérification que la méthode renvoie -1 pour un utilisateur inexistant
    if (points == -1) {
        cout << "  OK: getPoints a correctement renvoyé -1 pour un utilisateur inexistant" << endl;
        return true;
    } else {
        cout << "  ERREUR: getPoints a renvoyé " << points << " au lieu de -1 pour un utilisateur inexistant" << endl;
        return false;
    }
} //----- Fin de testGetPointsUtilisateurInexistant

bool services_tests::testGetPointsUtilisateurExistant()
// Algorithme : teste la méthode getPoints avec un utilisateur qui existe
{
    cout << "T27: Test de getPoints avec un utilisateur existant" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    string userId = "User1";
    Session session(UserType::PARTICULIER, userId);
    AuthService authService;
    authService.setCurrentSession(session);

    PointsManager pointsManager(uda, &particulierData, sensors, &authService);

    // Test avec l'utilisateur existant
    int points = pointsManager.getPoints(userId);

    // Vérification que la méthode renvoie un nombre de points valide
    if (points >= 0) {
        cout << "  OK: getPoints a correctement renvoyé " << points << " points pour l'utilisateur " << userId << endl;
        return true;
    } else {
        cout << "  ERREUR: getPoints a renvoyé " << points << " pour un utilisateur existant" << endl;
        return false;
    }
} //----- Fin de testGetPointsUtilisateurExistant

bool services_tests::testExcludeSensorInexistant()
// Algorithme : teste la méthode excludeSensor avec un capteur qui n'existe pas
{
    cout << "T28: Test d'excludeSensor avec un capteur inexistant" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);
    AdminServices adminServices(uda, sensors, &authService);

    // Test avec un capteur inexistant
    string sensorId = "Sensor100";
    bool result = adminServices.excludeSensor(sensorId);

    // Vérification que la méthode renvoie false pour un capteur inexistant
    if (!result) {
        cout << "  OK: excludeSensor a correctement détecté que le capteur n'existe pas" << endl;
        return true;
    } else {
        cout << "  ERREUR: excludeSensor a renvoyé true pour un capteur inexistant" << endl;
        return false;
    }
} //----- Fin de testExcludeSensorInexistant

bool services_tests::testExcludeSensorDejaExclu()
// Algorithme : teste la méthode excludeSensor avec un capteur dont l'utilisateur est déjà exclu
{
    cout << "T29: Test d'excludeSensor avec un capteur dont l'utilisateur est déjà exclu" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);
    AdminServices adminServices(uda, sensors, &authService);

    // Test avec le capteur dont l'utilisateur est déjà exclu
    bool result = adminServices.excludeSensor("Sensor70");

    // Selon l'implémentation actuelle, excludeSensor devrait renvoyer true
    if (result) {
        cout << "  OK: excludeSensor a correctement géré le cas d'un utilisateur déjà exclu" << endl;
        return true;
    } else {
        cout << "  ERREUR: excludeSensor a échoué pour un utilisateur déjà exclu" << endl;
        return false;
    }
} //----- Fin de testExcludeSensorDejaExclu

bool services_tests::testExcludeSensorValide()
// Algorithme : teste la méthode excludeSensor avec un capteur valide
{
    cout << "T30: Test d'excludeSensor avec un capteur valide" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);
    AdminServices adminServices(uda, sensors, &authService);

    // Test avec un capteur valide
    string sensorId = "Sensor70";
    bool result = adminServices.excludeSensor(sensorId);

    // Vérification que l'utilisateur a bien été exclu
    if (result) {
        cout << "  OK: excludeSensor a correctement exclu l'utilisateur du capteur " << sensorId << endl;
        return true;
    } else {
        cout << "  ERREUR: excludeSensor a échoué pour un capteur valide" << endl;
        return false;
    }
} //----- Fin de testExcludeSensorValide

bool services_tests::testEvaluate()
// Algorithme : teste la méthode evaluate pour vérifier le bon fonctionnement de l'évaluation des capteurs
{
    cout << "T31: Test de evaluate" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    UserDataAccess uda;
    vector<ParticulierData> particulierData = uda.loadParticulierData("../data/ParticulierData.csv");

    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    AdminServices adminServices(uda, sensors, &authService);
    Statistics stats(sensors, cleaners, nullptr, &authService);

    // Test de l'évaluation des capteurs
    vector<double> result = adminServices.evaluate(stats);

    // Vérification que l'évaluation a été effectuée correctement
    if (!result.empty() && result[0] >= 0 && result[1] >= 0 && result[2] >= 0 && result[3] >= 0 && result[4] >= 0) {
        cout << "  OK: L'évaluation des services a été effectuée avec succès" << endl;
        return true;
    } else {
        cout << "  ERREUR: L'évaluation d'au moins un service a échoué" << endl;
        return false;
    }
} //----- Fin de testEvaluate

bool services_tests::testLoginCombiValide()
// Algorithme : teste la méthode login avec une combinaison valide
{
    cout << "T32: Test de login avec une combinaison valide" << endl;

    AuthService authService;

    // Test avec une combinaison login/mot de passe valide
    string credentialsFilePath = "../data/credentials.csv";
    string login = "admin";
    string password = "mdp";

    Session session = authService.login(credentialsFilePath, login, password);

    // Vérification que la session est valide
    if (session.getUserType() != UserType::UNDEFINED && !session.getUserId().empty()) {
        cout << "  OK: Login réussi, session valide créée pour " << login << endl;
        return true;
    } else {
        cout << "  ERREUR: Échec de login avec des identifiants valides" << endl;
        return false;
    }
} //----- Fin de testLoginCombiValide



bool services_tests::testLoginCombiInvalide()
// Algorithme : teste la méthode login avec une combinaison invalide
{
    cout << "T33: Test de login avec une combinaison invalide" << endl;

    AuthService authService;

    // Test avec une combinaison login/mot de passe invalide
    string credentialsFilePath = "../data/credentials.csv";
    string login = "admin";
    string password = "motDePasse";

    Session session = authService.login(credentialsFilePath, login, password);

    // Vérification que la session est invalide (type UNDEFINED)
    if (session.getUserType() == UserType::UNDEFINED && session.getUserId().empty()) {
        cout << "  OK: Login échoué comme prévu avec des identifiants invalides" << endl;
        return true;
    } else {
        cout << "  ERREUR: Login réussi avec des identifiants invalides" << endl;
        return false;
    }
} //----- Fin de testLoginCombiInvalide

bool services_tests::testCheckRequiredRolePrivilegeSuperieur()
// Algorithme : teste la méthode checkRequiredRole avec un rôle de session supérieur au rôle requis
{
    cout << "T34: Test de checkRequiredRole avec un rôle de session supérieur" << endl;

    // Création d'une session avec le rôle ADMIN
    Session session(UserType::ADMIN);
    AuthService authService;
    authService.setCurrentSession(session);

    // Test avec un rôle requis inférieur (USER)
    bool result = authService.checkRequiredRole(UserType::USER);

    // Vérification que l'accès est autorisé
    if (!result) {
        cout << "  OK: L'accès est refusé pour un rôle supérieur" << endl;
        return true;
    } else {
        cout << "  ERREUR: L'accès est autorisé pour un rôle supérieur" << endl;
        return false;
    }
} //----- Fin de testCheckRequiredRolePrivilegeSuperieur

bool services_tests::testCheckRequiredRolePrivilegeInferieur()
// Algorithme : teste la méthode checkRequiredRole avec un rôle de session inférieur au rôle requis
{
    cout << "T35: Test de checkRequiredRole avec un rôle de session inférieur" << endl;

    // Création d'une session avec le rôle FOURNISSEUR
    Session session(UserType::FOURNISSEUR);
    AuthService authService;
    authService.setCurrentSession(session);

    // Test avec un rôle requis différent (PARTICULIER)
    bool result = authService.checkRequiredRole(UserType::PARTICULIER);

    // Vérification que l'accès est refusé
    if (!result) {
        cout << "  OK: L'accès est refusé pour un rôle inférieur" << endl;
        return true;
    } else {
        cout << "  ERREUR: L'accès est autorisé pour un rôle inférieur" << endl;
        return false;
    }
} //----- Fin de testCheckRequiredRolePrivilegeInferieur

//-------------------------------------------- Constructeurs - destructeur
services_tests::services_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <services_tests>" << endl;
#endif
} //----- Fin de services_tests

services_tests::~services_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <services_tests>" << endl;
#endif
} //----- Fin de ~services_tests

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
