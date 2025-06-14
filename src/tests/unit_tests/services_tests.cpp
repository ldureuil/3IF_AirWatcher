/*************************************************************************
services_tests  -  tests unitaires des méthodes de la couche services
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <services_tests> (fichier services_tests.cpp) -

//---------------------------------------------------------------- INCLUDE
#include "../../Services/PointsManager.h"
#include "../../Data/ParticulierData.h"
#include "../../Data/Sensor.h"
#include "../../Data/Measurement.h"
#include "../../Authentification/AuthService.h"
#include "../../DataAccess/UserDataAccess.h"



//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "services_tests.h"
#include <cassert>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC
//----------------------------------------------------- Méthodes publiques

class MockAuthService : public AuthService {
public:
    bool checkRequiredRole(UserType type) override {
        return true; // Simule que l'utilisateur a le rôle requis
    }
};


void services_tests::runTests()
{
    // Implémentez ici les tests unitaires pour les méthodes de la couche Services
    cout << "Running services tests..." << endl;

    // Test de la méthode award
    //Initialisation des données de test
    ParticulierData u1("User1", 0, false), u2("User2", 0,false), exclu("Excluded", 0,false);

    Measurement m1(time(nullptr), "temp", "C", "Temperature", 25.0);
    vector<Measurement> measurements = {m1};
    Sensor s1("Sensor4", 0, 0, measurements,"User2");
    Sensor s2("Sensor5", 0, 0, measurements,"User3");
    Sensor s3("Sensor6", 0, 0, measurements,"Excluded");
    Sensor sa("SensorA", 0, 0, measurements,""); // no tiene usuario asociado
    vector<ParticulierData> particuliers = { u1, u2, exclu };
    MockAuthService auth;
    UserDataAccess uda;

    // Test T17: liste vide
    {
        vector<Sensor> sensors;
        const vector<string> sensorsUsed;
        
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award(sensorsUsed);
        assert(result == true);
        cout << "T17 passed." << endl;
    }

    // Test T18: 1 capteur valide
    {
        vector<Sensor> sensors = { s1 };
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor1" });
        assert(result == true);
        cout << "T18 passed." << endl;
    }

    // Test T19: 2 capteurs, 2 utilisateurs différents
    {
        vector<Sensor> sensors = { s1, s2 };
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor1", "Sensor2" });
        assert(result == true);
        cout << "T19 passed." << endl;
    }

    // Test T20: 2 capteurs du même utilisateur
    {
        vector<Sensor> sensors = { s1 };

        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor1", "Sensor1" });
        assert(result == true);
        cout << "T20 passed." << endl;
    }

    // Test T21: capteur inconnu
    {
        vector<Sensor> sensors = { s1 };
  
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor999" });
        assert(result == false);
        cout << "T21 passed." << endl;
    }

    // Test T22: capteur exclu
    {
        vector<Sensor> sensors = { s3 };
       
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor3" });
        assert(result == false);
        cout << "T22 passed." << endl;
    }

    // Test T23: capteur valide + capteur exclu
    {
        vector<Sensor> sensors = { s1, s3 };
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor1", "Sensor3" });
        assert(result == false);
        cout << "T23 passed." << endl;
    }

    // Test T24: capteur sans utilisateur
    {
        vector<Sensor> sensors = { sa };

        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "SensorA" });
        assert(result == true);
        cout << "T24 passed." << endl;
    }

    // Test T25: capteur valide + capteur sans utilisateur
    {
        vector<Sensor> sensors = { s1, sa };
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.award({ "Sensor1", "SensorA" });
        assert(result == true);
        cout << "T25 passed." << endl;
    }

    //Test T26 : Utilisateur inexistant
    {
        vector<Sensor> sensors = { s1 };
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        bool result = pm.getPoints("nonExistentUser");
        assert(result == -1);
        cout << "T26 passed." << endl;
    }

    //Test T27 : Utilisateur existant
    {
        vector<Sensor> sensors = { s1 };
        PointsManager pm(uda, &particuliers, &sensors, &auth);

        int points = pm.getPoints("User1");
        assert(points >= 0); 
        cout << "T27 passed." << endl;
    }


    cout << "Services tests completed." << endl;
} //----- Fin de runTests

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
