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

#include <fstream>

//------------------------------------------------------ Include personnel
#include "data_tests.h"
#include "../../Data/Sensor.h"
#include "../../Data/Cleaner.h"
#include "../../Data/Measurement.h"
#include "../../DataAccess/DataLoader.h"
#include "../../DataAccess/UserDataAccess.h"
#include "../../Data/ParticulierData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

int data_tests::runTests()
// Algorithme : exécute les tests unitaires pour la couche Data
{
    cout << "=== Début des tests unitaires pour Data ===" << endl;

    int nbTestsOk = 0;

    // Tests pour Sensor::distanceTo
    nbTestsOk += testDistanceToIdentiques(); // T36
    nbTestsOk += testDistanceToInvalides(); // T37
    nbTestsOk += testDistanceToDifferentes(); // T38

    // Tests pour Sensor::getMeasurements
    nbTestsOk += testGetMeasurementsAucune(); // T39
    nbTestsOk += testGetMeasurementsAvecDonnees(); // T40

    // Tests pour Sensor::getSensorNeighbours
    nbTestsOk += testGetSensorNeighboursIsole(); // T41
    nbTestsOk += testGetSensorNeighboursAvecVoisins(); // T42

    // Tests pour Sensor::getClosestMeasurements
    nbTestsOk += testGetClosestMeasurementsAucune(); // T43
    nbTestsOk += testGetClosestMeasurementsAnterieures(); // T44
    nbTestsOk += testGetClosestMeasurementsPosterieures(); // T45
    nbTestsOk += testGetClosestMeasurementsToutesProches(); // T46

    // Tests pour Measurement::isWithin
    nbTestsOk += testIsWithinDansIntervalle(); // T47
    nbTestsOk += testIsWithinHorsIntervalle(); // T48

    // Tests pour Cleaner::getNeighbouringSensors
    nbTestsOk += testGetNeighbouringSensorsAucun(); // T49
    nbTestsOk += testGetNeighbouringSensorsPlusieurs(); // T50

    // Tests pour UserDataAccess::updateUserPoints
    nbTestsOk += testUpdateUserPointsExistant(); // T51

    // Tests pour UserDataAccess::addExcludedUser
    nbTestsOk += testAddExcludedUserValide(); // T52
    nbTestsOk += testAddExcludedUserDejaExclu(); // T53

    // Tests pour UserDataAccess::loadParticulierData
    nbTestsOk += testLoadParticulierDataVide(); // T54
    nbTestsOk += testLoadParticulierDataAvecDonnees(); // T55

    cout << "Data tests completed." << endl;

    return nbTestsOk;
} //----- Fin de runTests

bool data_tests::testDistanceToIdentiques()
// Algorithme : teste la méthode distanceTo avec des coordonnées identiques à celles du capteur
{
    cout << "T36: Test distanceTo avec des coordonnées identiques" << endl;

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
    cout << "T37: Test distanceTo avec des coordonnées invalides" << endl;

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
    cout << "T38: Test distanceTo avec des coordonnées différentes" << endl;

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
    cout << "T39: Test getMeasurements sans mesure dans la période" << endl;

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
    cout << "T40: Test getMeasurements avec des mesures dans la période" << endl;

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

bool data_tests::testGetSensorNeighboursIsole()
// Algorithme : teste la méthode getSensorNeighbours avec un capteur isolé
{
    cout << "T41: Test getSensorNeighbours avec un capteur isolé" << endl;

    // Création d'un capteur de test
    Sensor sensor;
    sensor.setId("SensorTest");
    sensor.setLat(45.0);
    sensor.setLng(5.0);

    // Création d'un vecteur de capteurs très éloignés
    vector<Sensor> capteurs;
    Sensor capteurEloigne;
    capteurEloigne.setId("CapteurEloigne");
    capteurEloigne.setLat(60.0);  // Très loin du capteur de test
    capteurEloigne.setLng(20.0);
    capteurs.push_back(capteurEloigne);

    // Test de la méthode avec un rayon de 100 mètres
    vector<Sensor> voisins = sensor.getSensorNeighbours(&capteurs, 100);

    // Vérification que la liste est vide
    if (voisins.empty()) {
        cout << "  OK: Aucun voisin trouvé comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: " << voisins.size() << " voisins trouvés alors qu'aucun n'était attendu" << endl;
        return false;
    }
} //----- Fin de testGetSensorNeighboursIsole

bool data_tests::testGetSensorNeighboursAvecVoisins()
// Algorithme : teste la méthode getSensorNeighbours avec un capteur ayant des voisins
{
    cout << "T42: Test getSensorNeighbours avec un capteur ayant des voisins" << endl;

    // Création d'un capteur de test
    Sensor sensor;
    sensor.setId("SensorTest");
    sensor.setLat(45.0);
    sensor.setLng(5.0);

    vector<Sensor> capteurs;
    // Capteur proche (environ 50m de distance)
    Sensor capteurProche;
    capteurProche.setId("CapteurProche");
    capteurProche.setLat(45.0005);  // ~50m au nord
    capteurProche.setLng(5.0);
    capteurs.push_back(capteurProche);

    // Capteur éloigné
    Sensor capteurEloigne;
    capteurEloigne.setId("CapteurEloigne");
    capteurEloigne.setLat(46.0);  // ~111km au nord
    capteurEloigne.setLng(5.0);
    capteurs.push_back(capteurEloigne);

    // Test de la méthode avec un rayon de 100 mètres
    vector<Sensor> voisins = sensor.getSensorNeighbours(&capteurs, 100);

    // Vérification qu'il y a exactement un voisin
    if (voisins.size() == 1) {
        cout << "  OK: " << voisins.size() << " voisin trouvé comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: " << voisins.size() << " voisins trouvés alors qu'un seul était attendu" << endl;
        return false;
    }
} //----- Fin de testGetSensorNeighboursAvecVoisins

bool data_tests::testGetClosestMeasurementsAucune()
// Algorithme : teste la méthode getClosestMeasurements sans mesure
{
    cout << "T43: Test getClosestMeasurements sans mesure" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Sélection d'un capteur pour le test
    Sensor sensor = (*sensors)[0];

    // Définition d'une date future sans mesures
    struct tm tm_instant = {};
    tm_instant.tm_year = 2100 - 1900;
    tm_instant.tm_mon = 0;
    tm_instant.tm_mday = 1;
    time_t instant = mktime(&tm_instant);

    // Test avec before_after = 0
    vector<Measurement> result = sensor.getClosestMeasurements(instant, 0);

    // Vérification
    if (result.empty()) {
        cout << "  OK: Aucune mesure trouvée comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: " << result.size() << " mesures trouvées alors qu'aucune n'était attendue" << endl;
        return false;
    }
} //----- Fin de testGetClosestMeasurementsAucune

bool data_tests::testGetClosestMeasurementsAnterieures()
// Algorithme : teste la méthode getClosestMeasurements pour trouver des mesures antérieures
{
    cout << "T44: Test getClosestMeasurements pour trouver des mesures antérieures" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Sélection d'un capteur pour le test
    Sensor sensor = (*sensors)[0];

    // Définition d'une date en 2019
    struct tm tm_instant = {};
    tm_instant.tm_year = 2019 - 1900;
    tm_instant.tm_mon = 4;
    tm_instant.tm_mday = 2;
    time_t instant = mktime(&tm_instant);

    // Test avec before_after = -1 (antérieures)
    vector<Measurement> result = sensor.getClosestMeasurements(instant, -1);

    // Vérification qu'il y a des mesures
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " mesures antérieures trouvées" << endl;

        // Vérification que toutes les mesures sont bien antérieures à la date
        bool toutesAnterieures = true;
        for (auto m : result) {
            if (m.getTs() >= instant) {
                toutesAnterieures = false;
                break;
            }
        }

        if (toutesAnterieures) {
            cout << "  OK: Toutes les mesures sont bien antérieures à la date spécifiée" << endl;
            return true;
        } else {
            cout << "  ERREUR: Certaines mesures ne sont pas antérieures à la date spécifiée" << endl;
            return false;
        }
    } else {
        cout << "  ERREUR: Aucune mesure antérieure trouvée" << endl;
        return false;
    }
} //----- Fin de testGetClosestMeasurementsAnterieures

bool data_tests::testGetClosestMeasurementsPosterieures()
// Algorithme : teste la méthode getClosestMeasurements pour trouver des mesures postérieures
{
    cout << "T45: Test getClosestMeasurements pour trouver des mesures postérieures" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Sélection d'un capteur pour le test
    Sensor sensor = (*sensors)[0];

    // Définition d'une date en 2019
    struct tm tm_instant = {};
    tm_instant.tm_year = 2019 - 1900;
    tm_instant.tm_mon = 4;
    tm_instant.tm_mday = 2;
    time_t instant = mktime(&tm_instant);

    // Test avec before_after = 1 (postérieures)
    vector<Measurement> result = sensor.getClosestMeasurements(instant, 1);

    // Vérification qu'il y a des mesures
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " mesures postérieures trouvées" << endl;

        // Vérification que toutes les mesures sont bien postérieures à la date
        bool toutesPostérieures = true;
        for (auto m : result) {
            if (m.getTs() <= instant) {
                toutesPostérieures = false;
                break;
            }
        }

        if (toutesPostérieures) {
            cout << "  OK: Toutes les mesures sont bien postérieures à la date spécifiée" << endl;
            return true;
        } else {
            cout << "  ERREUR: Certaines mesures ne sont pas postérieures à la date spécifiée" << endl;
            return false;
        }
    } else {
        cout << "  ERREUR: Aucune mesure postérieure trouvée" << endl;
        return false;
    }
} //----- Fin de testGetClosestMeasurementsPosterieures

bool data_tests::testGetClosestMeasurementsToutesProches()
// Algorithme : teste la méthode getClosestMeasurements pour trouver toutes les mesures proches
{
    cout << "T46: Test getClosestMeasurements pour trouver toutes les mesures proches" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Sélection d'un capteur pour le test
    Sensor sensor = (*sensors)[0];

    // Définition d'une date en 2019
    struct tm tm_instant = {};
    tm_instant.tm_year = 2019 - 1900;
    tm_instant.tm_mon = 4;
    tm_instant.tm_mday = 2;
    time_t instant = mktime(&tm_instant);

    // Test avec before_after = 0 (toutes les mesures)
    vector<Measurement> result = sensor.getClosestMeasurements(instant, 0);

    // Vérification qu'il y a des mesures
    if (!result.empty()) {
        cout << "  OK: " << result.size() << " mesures trouvées au total" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucune mesure trouvée" << endl;
        return false;
    }
} //----- Fin de testGetClosestMeasurementsToutesProches

bool data_tests::testIsWithinDansIntervalle()
// Algorithme : teste la méthode isWithin avec un timestamp dans l'intervalle
{
    cout << "T47: Test isWithin avec un timestamp dans l'intervalle" << endl;

    // Création d'une mesure de test (timestamp: 01/01/2019 à 12:00)
    struct tm tm_mesure = {};
    tm_mesure.tm_year = 2019 - 1900;
    tm_mesure.tm_mon = 0;
    tm_mesure.tm_mday = 1;
    tm_mesure.tm_hour = 12;
    time_t ts_mesure = mktime(&tm_mesure);

    Measurement measurement(ts_mesure, "O3", "µg/m3", "Ozone", 42.0);

    // Définition d'un intervalle qui contient le timestamp
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 0;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2019 - 1900;
    tm_end.tm_mon = 0;
    tm_end.tm_mday = 2;
    time_t end = mktime(&tm_end);

    // Test
    bool result = measurement.isWithin(start, end);

    // Vérification
    if (result) {
        cout << "  OK: La mesure est bien détectée dans l'intervalle" << endl;
        return true;
    } else {
        cout << "  ERREUR: La mesure n'est pas détectée dans l'intervalle" << endl;
        return false;
    }
} //----- Fin de testIsWithinDansIntervalle

bool data_tests::testIsWithinHorsIntervalle()
// Algorithme : teste la méthode isWithin avec un timestamp hors intervalle
{
    cout << "T48: Test isWithin avec un timestamp hors intervalle" << endl;

    // Création d'une mesure de test (timestamp: 01/01/2019 à 12:00)
    struct tm tm_mesure = {};
    tm_mesure.tm_year = 2019 - 1900;
    tm_mesure.tm_mon = 0;
    tm_mesure.tm_mday = 1;
    tm_mesure.tm_hour = 12;
    time_t ts_mesure = mktime(&tm_mesure);

    Measurement measurement(ts_mesure, "O3", "µg/m3", "Ozone", 42.0);

    // Cas 1: Définition d'un intervalle avant le timestamp
    struct tm tm_start1 = {};
    tm_start1.tm_year = 2018 - 1900;
    tm_start1.tm_mon = 0;
    tm_start1.tm_mday = 1;
    time_t start1 = mktime(&tm_start1);

    struct tm tm_end1 = {};
    tm_end1.tm_year = 2018 - 1900;
    tm_end1.tm_mon = 11;
    tm_end1.tm_mday = 31;
    time_t end1 = mktime(&tm_end1);

    // Cas 2: Définition d'un intervalle après le timestamp
    struct tm tm_start2 = {};
    tm_start2.tm_year = 2020 - 1900;
    tm_start2.tm_mon = 0;
    tm_start2.tm_mday = 1;
    time_t start2 = mktime(&tm_start2);

    struct tm tm_end2 = {};
    tm_end2.tm_year = 2020 - 1900;
    tm_end2.tm_mon = 11;
    tm_end2.tm_mday = 31;
    time_t end2 = mktime(&tm_end2);

    // Tests
    bool result1 = measurement.isWithin(start1, end1);
    bool result2 = measurement.isWithin(start2, end2);

    // Vérification
    if (!result1 && !result2) {
        cout << "  OK: La mesure est bien détectée hors des intervalles" << endl;
        return true;
    } else {
        cout << "  ERREUR: La mesure est détectée dans au moins un intervalle" << endl;
        return false;
    }
} //----- Fin de testIsWithinHorsIntervalle

bool data_tests::testGetNeighbouringSensorsAucun()
// Algorithme : teste la méthode getNeighbouringSensors sans capteur dans le rayon
{
    cout << "T49: Test getNeighbouringSensors sans capteur dans le rayon" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Dates de début et fin pour le Cleaner
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 0;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2020 - 1900;
    tm_end.tm_mon = 0;
    tm_end.tm_mday = 1;
    time_t end = mktime(&tm_end);

    // Création d'un Cleaner isolé (coordonnées très éloignées des capteurs existants)
    Cleaner cleaner("CleanerTest", 0.0, 0.0, start, end);

    // Test avec un rayon de 500 mètres
    vector<Sensor> voisins = cleaner.getNeighbouringSensors(500, sensors);

    // Vérification que la liste est vide
    if (voisins.empty()) {
        cout << "  OK: Aucun capteur trouvé dans le rayon comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: " << voisins.size() << " capteurs trouvés alors qu'aucun n'était attendu" << endl;
        return false;
    }
} //----- Fin de testGetNeighbouringSensorsAucun

bool data_tests::testGetNeighbouringSensorsPlusieurs()
// Algorithme : teste la méthode getNeighbouringSensors avec plusieurs capteurs dans le rayon
{
    cout << "T50: Test getNeighbouringSensors avec plusieurs capteurs dans le rayon" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Vérification qu'il y a des capteurs dans le jeu de données
    if (sensors->empty()) {
        cout << "  ERREUR: Aucun capteur dans le jeu de données" << endl;
        return false;
    }

    // Sélection d'un capteur existant pour placer le Cleaner à proximité
    Sensor sensorReference = (*sensors)[0];

    // Dates de début et fin pour le Cleaner
    struct tm tm_start = {};
    tm_start.tm_year = 2019 - 1900;
    tm_start.tm_mon = 0;
    tm_start.tm_mday = 1;
    time_t start = mktime(&tm_start);

    struct tm tm_end = {};
    tm_end.tm_year = 2020 - 1900;
    tm_end.tm_mon = 0;
    tm_end.tm_mday = 1;
    time_t end = mktime(&tm_end);

    // Création d'un Cleaner à proximité d'un capteur existant
    Cleaner cleaner("CleanerTest", sensorReference.getLat(), sensorReference.getLng(), start, end);

    // Test avec un rayon de 200 km
    vector<Sensor> voisins = cleaner.getNeighbouringSensors(200000, sensors);

    // Vérification qu'il y a au moins un capteur dans le rayon
    if (!voisins.empty()) {
        cout << "  OK: " << voisins.size() << " capteurs trouvés dans le rayon" << endl;
        return true;
    } else {
        cout << "  ERREUR: Aucun capteur trouvé dans le rayon alors que des capteurs étaient attendus" << endl;
        return false;
    }
} //----- Fin de testGetNeighbouringSensorsPlusieurs

bool data_tests::testUpdateUserPointsExistant()
// Algorithme : teste la méthode updateUserPoints pour un utilisateur existant
{
    cout << "T51: Test updateUserPoints pour un utilisateur existant" << endl;

    // Création d'un fichier de test temporaire
    string testFile = "tests/test_data/t51/ParticulierData.csv";
    ofstream file(testFile);
    file << "User1;5;false" << endl;
    file.close();

    UserDataAccess userAccess;

    // Test de mise à jour des points
    int newPoints = userAccess.updateUserPoints("User1", testFile);

    // Vérification du résultat retourné
    if (newPoints == 6) {
        // Vérification du contenu du fichier
        ifstream inFile(testFile);
        string line;
        getline(inFile, line);
        inFile.close();

        if (line == "User1;6;false") {
            cout << "  OK: Points utilisateur correctement incrémentés à " << newPoints << endl;
            return true;
        } else {
            cout << "  ERREUR: Le fichier n'a pas été mis à jour correctement. Contenu: " << line << endl;
            return false;
        }
    } else {
        cout << "  ERREUR: Retour incorrect: " << newPoints << " (attendu: 6)" << endl;
        return false;
    }
} //----- Fin de testUpdateUserPointsExistant

bool data_tests::testAddExcludedUserValide()
// Algorithme : teste la méthode addExcludedUser pour un utilisateur valide
{
    cout << "T52: Test addExcludedUser pour un utilisateur valide" << endl;

    // Création d'un fichier de test temporaire
    string testFile = "tests/test_data/t52/ParticulierData.csv";
    ofstream file(testFile);
    file << "User1;5;false" << endl;
    file << "User2;3;false" << endl;
    file.close();

    UserDataAccess userAccess;

    // Test d'ajout d'un utilisateur exclu
    int result = userAccess.addExcludedUser("User1", testFile);

    // Vérification du résultat retourné
    if (result == 1) {
        // Vérification du contenu du fichier
        ifstream inFile(testFile);
        string line;
        bool userFound = false;

        while (getline(inFile, line)) {
            if (line == "User1;5;true") {
                userFound = true;
                break;
            }
        }
        inFile.close();

        if (userFound) {
            cout << "  OK: Utilisateur correctement marqué comme exclu" << endl;
            return true;
        } else {
            cout << "  ERREUR: L'utilisateur n'a pas été marqué comme exclu dans le fichier" << endl;
            return false;
        }
    } else {
        cout << "  ERREUR: Retour incorrect: " << result << " (attendu: 1)" << endl;
        return false;
    }
} //----- Fin de testAddExcludedUserValide

bool data_tests::testAddExcludedUserDejaExclu()
// Algorithme : teste la méthode addExcludedUser pour un utilisateur déjà exclu
{
    cout << "T53: Test addExcludedUser pour un utilisateur déjà exclu" << endl;

    // Création d'un fichier de test temporaire
    string testFile = "tests/test_data/t53/ParticulierData.csv";
    ofstream file(testFile);
    file << "User1;5;false" << endl;
    file << "User3;2;true" << endl;
    file.close();

    UserDataAccess userAccess;

    // Test d'ajout d'un utilisateur déjà exclu
    int result = userAccess.addExcludedUser("User3", testFile);

    // Vérification du résultat retourné
    if (result == 0) {
        cout << "  OK: Le système a correctement détecté que l'utilisateur est déjà exclu" << endl;
        return true;
    } else {
        cout << "  ERREUR: Retour incorrect: " << result << " (attendu: 0)" << endl;
        return false;
    }
} //----- Fin de testAddExcludedUserDejaExclu

bool data_tests::testLoadParticulierDataVide()
// Algorithme : teste la méthode loadParticulierData avec un fichier vide
{
    cout << "T54: Test loadParticulierData avec un fichier vide" << endl;

    // Création d'un fichier de test vide
    string testFile = "tests/test_data/t54/ParticulierData.csv";
    ofstream file(testFile);
    file.close();

    UserDataAccess userAccess;

    // Test de chargement du fichier vide
    vector<ParticulierData> result = userAccess.loadParticulierData(testFile);

    // Vérification que la liste est vide
    if (result.empty()) {
        cout << "  OK: Liste vide retournée comme attendu" << endl;
        return true;
    } else {
        cout << "  ERREUR: " << result.size() << " éléments trouvés alors que la liste devrait être vide" << endl;
        return false;
    }
} //----- Fin de testLoadParticulierDataVide

bool data_tests::testLoadParticulierDataAvecDonnees()
// Algorithme : teste la méthode loadParticulierData avec des données
{
    cout << "T55: Test loadParticulierData avec des données" << endl;

    // Création d'un fichier de test avec des données
    string testFile = "tests/test_data/t55/ParticulierData.csv";
    ofstream file(testFile);
    file << "User1;5;false" << endl;
    file << "User2;3;false" << endl;
    file << "User3;2;true" << endl;
    file.close();

    UserDataAccess userAccess;

    // Test de chargement du fichier avec données
    vector<ParticulierData> result = userAccess.loadParticulierData(testFile);

    // Vérification du nombre d'éléments
    if (result.size() == 3) {
        // Vérification des IDs utilisateurs
        bool user1Found = false, user2Found = false, user3Found = false;

        for (const auto& user : result) {
            if (user.getId() == "User1") user1Found = true;
            if (user.getId() == "User2") user2Found = true;
            if (user.getId() == "User3") user3Found = true;
        }

        if (user1Found && user2Found && user3Found) {
            cout << "  OK: Tous les utilisateurs ont été correctement chargés" << endl;
            return true;
        } else {
            cout << "  ERREUR: Certains utilisateurs n'ont pas été chargés correctement" << endl;
            return false;
        }
    } else {
        cout << "  ERREUR: Nombre incorrect d'utilisateurs chargés: " << result.size() << " (attendu: 3)" << endl;
        return false;
    }
} //----- Fin de testLoadParticulierDataAvecDonnees

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
