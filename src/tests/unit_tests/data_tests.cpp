/*************************************************************************
data_tests  -  tests unitaires des méthodes de la couche Data
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---- Réalisation de la classe <data_tests> (fichier data_tests.cpp) ----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "data_tests.h"
#include "../../Data/Sensor.h"
#include "../../Data/Measurement.h"
#include "../../DataAccess/DataLoader.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int data_tests::runTests()
// Algorithme : exécute les tests unitaires pour la couche Data
{
    cout << "Running data tests..." << endl;

    int nbTestsOk = 0;

    // Tests pour Sensor::distanceTo
    nbTestsOk += testDistanceToIdentiques(); // T36
    nbTestsOk += testDistanceToInvalides(); // T37
    nbTestsOk += testDistanceToDifferentes(); // T38

    // Tests pour Sensor::getMeasurements
    nbTestsOk += testGetMeasurementsAucune(); // T39
    nbTestsOk += testGetMeasurementsAvecDonnees(); // T40

    cout << "Data tests completed." << endl;

    return nbTestsOk;
} //----- Fin de runTests

bool data_tests::testDistanceToIdentiques()
// Algorithme : teste la méthode distanceTo avec des coordonnées identiques à celles du capteur
{
    cout << "T35: Test distanceTo avec des coordonnées identiques" << endl;

    // Création d'un capteur de test
    Sensor sensor;
    sensor.setId("SensorTest");
    sensor.setLat(45.0);
    sensor.setLng(5.0);

    // Test avec les mêmes coordonnées
    double result = sensor.distanceTo(45.0, 5.0);

    // Vérification
    if (abs(result) < 0.001) {  // Tolérance pour les erreurs d'arrondi
        cout << "  OK: Distance = " << result << " (attendu: 0.0)" << endl;
        return true;
    } else {
        cout << "  ERREUR: Distance = " << result << " (attendu: 0.0)" << endl;
        return false;
    }
} //----- Fin de testDistanceToIdentiques

bool data_tests::testDistanceToInvalides()
// Algorithme : teste la méthode distanceTo avec des coordonnées invalides
{
    cout << "T36: Test distanceTo avec des coordonnées invalides" << endl;

    // Création d'un capteur de test
    Sensor sensor;
    sensor.setId("SensorTest");
    sensor.setLat(45.0);
    sensor.setLng(5.0);

    // Test avec des coordonnées invalides
    double result = sensor.distanceTo(-14.0, 999999.99);

    // Note: La méthode distanceTo n'effectue pas de validation des coordonnées
    // Elle retourne toujours une distance même avec des coordonnées invalides

    // Vérification que la distance est positive (comportement réel)
    if (result > 0) {
        cout << "  OK: Distance calculée = " << result << " mètres (attendu: valeur positive)" << endl;
        return true;
    } else {
        cout << "  ERREUR: Distance calculée invalide = " << result << endl;
        return false;
    }
} //----- Fin de testDistanceToInvalides

bool data_tests::testDistanceToDifferentes()
// Algorithme : teste la méthode distanceTo avec des coordonnées différentes
{
    cout << "T37: Test distanceTo avec des coordonnées différentes" << endl;

    // Création d'un capteur de test
    Sensor sensor;
    sensor.setId("SensorTest");
    sensor.setLat(45.0);
    sensor.setLng(5.0);

    // Test avec des coordonnées différentes
    double result = sensor.distanceTo(45.1, 5.1);

    // Vérification que la distance est positive
    if (result > 0) {
        cout << "  OK: Distance = " << result << " mètres (attendu: valeur positive)" << endl;
        return true;
    } else {
        cout << "  ERREUR: Distance = " << result << " (attendu: valeur positive)" << endl;
        return false;
    }
} //----- Fin de testDistanceToDifferentes

bool data_tests::testGetMeasurementsAucune()
// Algorithme : teste la méthode getMeasurements sans mesure dans la période
{
    cout << "T38: Test getMeasurements sans mesure dans la période" << endl;

    // Chargement des capteurs depuis les données
    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Sélection d'un capteur pour le test
    Sensor sensor = (*sensors)[0];

    // Définition d'une période sans mesures (date future)
    struct tm tm_start = {};
    tm_start.tm_year = 2100 - 1900;
    tm_start.tm_mon = 0;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2100 - 1900;
    tm_end.tm_mon = 0;
    tm_end.tm_mday = 2;
    time_t end = mktime(&tm_end);

    // Test
    vector<Measurement> result = sensor.getMeasurements(start, end);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucune mesure trouvée comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: " << result.size() << " mesures trouvées alors qu'aucune n'était attendue" << endl;
        return false;
    }
} //----- Fin de testGetMeasurementsAucune

bool data_tests::testGetMeasurementsAvecDonnees()
// Algorithme : teste la méthode getMeasurements avec des mesures dans la période
{
    cout << "T39: Test getMeasurements avec des mesures dans la période" << endl;

    // Chargement des capteurs depuis les données
    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Sélection d'un capteur pour le test
    Sensor sensor = (*sensors)[0];

    // Définition d'une période avec mesures (2019)
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 0;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 11;
    tm_end.tm_mday = 31;
    time_t end = mktime(&tm_end);

    // Test
    vector<Measurement> result = sensor.getMeasurements(start, end);

    // Vérification
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " mesures trouvées dans la période" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucune mesure trouvée alors que des données étaient attendues" << endl;
        return false;
    }
} //----- Fin de testGetMeasurementsAvecDonnees

//-------------------------------------------- Constructeurs - destructeur
data_tests::data_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <data_tests>" << endl;
#endif
} //----- Fin de data_tests

data_tests::~data_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <data_tests>" << endl;
#endif
} //----- Fin de ~data_tests

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
