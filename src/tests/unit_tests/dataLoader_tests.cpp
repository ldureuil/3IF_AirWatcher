/*************************************************************************
dataLoader_tests  -  tests unitaires des méthodes de la couche DataLoader
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <dataLoader_tests> (fichier dataLoader_tests.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "dataLoader_tests.h"
#include "../../DataAccess/DataLoader.h"
#include "../../DataAccess/AuthDataAccess.h"
#include "../../Data/Sensor.h"
#include "../../Data/Cleaner.h"
#include "../../Data/Credentials.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int dataLoader_tests::runTests()
// Algorithme : exécute les tests unitaires pour la couche DataLoader
{
    cout << "=== Début des tests unitaires pour DataLoader ===" << endl;

    int nbTestsOk = 0;

    // Tests pour loadSensor
    nbTestsOk += testLoadSensorWithData();    // T64
    nbTestsOk += testLoadSensorWithEmptyData(); // T65

    // Tests pour loadCleaner
    nbTestsOk += testLoadCleanerWithData();    // T66
    nbTestsOk += testLoadCleanerWithEmptyData(); // T67

    // Tests pour AuthDataAccess::findCredentials
    nbTestsOk += testFindCredentialsWithEmptyFile(); // T68
    nbTestsOk += testFindCredentialsWithData(); // T69
    nbTestsOk += testFindCredentialsWrongLogin(); // T70

    cout << "=== Fin des tests unitaires pour DataLoader ===" << endl;

    return nbTestsOk;
} //----- Fin de runTests

bool dataLoader_tests::testLoadSensorWithData()
// Algorithme : teste la méthode loadSensor avec la base de données entière
{
    cout << "T64: Test de loadSensor avec une base contenant plusieurs capteurs" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("../data");

    // Vérifier que les capteurs sont bien chargés
    if (sensors != nullptr && sensors->size() > 0) {
        cout << "  OK: " << sensors->size() << " capteurs chargés avec succès" << endl;
        return true;
    } else {
        cout << "  ERREUR: Échec du chargement des capteurs" << endl;
        return false;
    }
} //----- Fin de testLoadSensorWithData

bool dataLoader_tests::testLoadSensorWithEmptyData()
// Algorithme : teste la méthode loadSensor avec une base de données vide
{
    cout << "T65: Test de loadSensor avec une base vide" << endl;

    DataLoader dataLoader;
    vector<Sensor>* sensors = dataLoader.loadSensor("tests/test_data/t61");

    // Vérifier que le résultat est bien nullptr
    if (sensors != nullptr && sensors->empty()) {
        cout << "  OK: Retour vide pour une base vide" << endl;
        return true;
    } else {
        cout << "  ERREUR: Le résultat n'est pas vide pour une base vide" << endl;
        return false;
    }
} //----- Fin de testLoadSensorWithEmptyData

bool dataLoader_tests::testLoadCleanerWithData()
// Algorithme : teste la méthode loadCleaner avec la base de données entière
{
    cout << "T66: Test de loadCleaner avec une base contenant plusieurs cleaners" << endl;

    DataLoader dataLoader;
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("../data");

    // Vérifier que les cleaners sont bien chargés
    if (cleaners != nullptr && cleaners->size() > 0) {
        cout << "  OK: " << cleaners->size() << " cleaners chargés avec succès" << endl;
        return true;
    } else {
        cout << "  ERREUR: Échec du chargement des cleaners" << endl;
        return false;
    }
} //----- Fin de testLoadCleanerWithData

bool dataLoader_tests::testLoadCleanerWithEmptyData()
// Algorithme : teste la méthode loadCleaner avec une base de données vide
{
    cout << "T67: Test de loadCleaner avec une base vide" << endl;

    DataLoader dataLoader;
    vector<Cleaner>* cleaners = dataLoader.loadCleaner("tests/test_data/t63");

    // Vérifier que le résultat est vide
    if (cleaners != nullptr && cleaners->empty()) {
        cout << "  OK: Retour vide pour une base vide" << endl;
        return true;
    } else {
        cout << "  ERREUR: Le résultat n'est pas vide pour une base vide" << endl;
        return false;
    }
} //----- Fin de testLoadCleanerWithEmptyData

bool dataLoader_tests::testFindCredentialsWithEmptyFile() {
    cout << "T68: Test de findCredentials avec un fichier CSV vide" << endl;

    AuthDataAccess authDA;
    Credentials cred = authDA.findCredentials("tests/test_data/t64/credentials.csv", "user", "pass");

    // Vérifier que les credentials sont vides
    if (cred.getLogin().empty()) {
        cout << "  OK: Credentials vides retournées pour un fichier vide" << endl;
        return true;
    } else {
        cout << "  ERREUR: Des credentials non vides ont été retournées" << endl;
        return false;
    }
} //----- Fin de testFindCredentialsWithEmptyFile

bool dataLoader_tests::testFindCredentialsWithData()
// Algorithme : teste la méthode findCredentials avec des données valides
{
    cout << "T69: Test de findCredentials avec des données" << endl;

    // Tester la méthode findCredentials
    AuthDataAccess authDA;
    Credentials cred = authDA.findCredentials("../data/credentials.csv", "admin", "mdp");

    // Vérifier que les bons credentials sont retournés
    if (cred.getLogin() == "admin" && cred.getPassword() == "mdp") {
        cout << "  OK: Credentials trouvées avec succès" << endl;
        return true;
    } else {
        cout << "  ERREUR: Échec de la recherche de credentials" << endl;
        return false;
    }
} //----- Fin de testFindCredentialsWithData

bool dataLoader_tests::testFindCredentialsWrongLogin()
// Algorithme : teste la méthode findCredentials avec un login inexistant
{
    cout << "T70: Test de findCredentials avec un login inexistant" << endl;

    // Tester la méthode findCredentials
    AuthDataAccess authDA;
    Credentials cred = authDA.findCredentials("../data/credentials.csv", "Addmin0", "mdp");

    // Vérifier que les bons credentials sont retournés
    if (cred.getLogin().empty() && cred.getPassword().empty()) {
        cout << "  OK: Aucun credentials trouvés" << endl;
        return true;
    } else {
        cout << "  ERREUR: login retournés" << endl;
        return false;
    }
} //----- Fin de testFindCredentialsWrongLogin


//-------------------------------------------- Constructeurs - destructeur
dataLoader_tests::dataLoader_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <dataLoader_tests>" << endl;
#endif
} //----- Fin de dataLoader_tests

dataLoader_tests::~dataLoader_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <dataLoader_tests>" << endl;
#endif
} //----- Fin de ~dataLoader_tests

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées