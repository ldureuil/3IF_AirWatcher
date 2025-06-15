/*************************************************************************
AdminServices  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <AdminServices> (fichier AdminServices.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AdminServices.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool AdminServices::excludeSensor( string sensorId, string pointsFile )
// Algorithme :
//
{
    // vérifie si l'utilisateur a les droits administrateur
    if (!authService->checkRequiredRole(UserType::ADMIN))
    {
        cerr << "Accès refusé : droits administrateur requis" << endl;
        return false;
    }

    bool exist = false;
    Sensor* sensorExclu; 
    for ( auto& sensor : *sensors )
    {
        if ( sensor.getId() == sensorId )
        {
            exist = true;
            sensorExclu = &sensor;
            break;
        }
    }

    if ( !exist )
    {
        cerr << "Erreur : Le capteur " << sensorId << " n'existe pas." << endl;
        return false;
    }

    string userId = sensorExclu->getUserId();
    if ( userId == "" )
    {
        cerr << "Erreur : Le capteur " << sensorId << " n'est pas associé à un utilisateur." << endl;
        return false;
    }
    uda.addExcludedUser(userId, pointsFile);

    return true;
} //----- Fin de excludeSensor


vector<double>  AdminServices::evaluate( Statistics & stats )
// Algorithme :
//
{
    // vérifie si l'utilisateur a les droits administrateur
    if (!authService->checkRequiredRole(UserType::ADMIN))
    {
        cerr << "Accès refusé : droits administrateur requis" << endl;
        return vector<double>();
    }

    std::cout << "\n=== Évaluation des performances des méthodes de Statistics ===\n";

    // Définir période fixe correspondant aux données
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

    // 1. computeZone
    try {
        t1 = std::chrono::high_resolution_clock::now();
        auto res1 = stats.computeZone(43.9600415, 4.3593173, start, end, 50000, 0, ""); // 50 km
        t2 = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << "computeZone() : " << duration1.count() << " ms" << std::endl;
        results.push_back(duration1.count());
    } catch (...) {
        std::cout << "Erreur lors de computeZone()" << std::endl;
        results.push_back(-1);
    }

    // 2. analyzeCleaner
    try {
        std::vector<Measurement> cleanerStats;
        if (stats.getCleanerByID("Cleaner0") != nullptr)
        {
            t1 = std::chrono::high_resolution_clock::now();
            cleanerStats = stats.analyzeCleaner("Cleaner0", 50000);
            t2 = std::chrono::high_resolution_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            std::cout << "analyzeCleaner() : " << duration2.count() << " ms" << std::endl;
            results.push_back(duration2.count());
        }
        else
        {
            std::cout << "Cleaner 'Cleaner0' introuvable → test ignoré." << std::endl;
            results.push_back(-1);
        }
    } catch (...) {
        std::cout << "Erreur lors de analyzeCleaner()" << std::endl;
        results.push_back(-1);
    }

    // 3. analyzeSensor
    try {
        if (stats.getSensorByID("Sensor0") != nullptr)
        {
            t1 = std::chrono::high_resolution_clock::now();
            int result = stats.analyzeSensor("Sensor0");
            t2 = std::chrono::high_resolution_clock::now();
            auto duration3 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            std::cout << "analyzeSensor() : " << duration3.count() << " ms (résultat : " << result << ")" << std::endl;
            results.push_back(duration3.count());
        }
        else
        {
            std::cout << "Sensor 'Sensor0' introuvable → test ignoré." << std::endl;
            results.push_back(-1);
        }
    } catch (...) {
        std::cout << "Erreur lors de analyzeSensor()" << std::endl;
        results.push_back(-1);
    }

    // 4. compareSensors
    try {
        if (stats.getSensorByID("Sensor0") != nullptr)
        {
            t1 = std::chrono::high_resolution_clock::now();
            auto similar = stats.compareSensors("Sensor0", start, end);
            t2 = std::chrono::high_resolution_clock::now();
            auto duration4 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
            std::cout << "compareSensors() : " << duration4.count() << " ms (" << similar.size() << " capteurs comparés)" << std::endl;
            results.push_back(duration4.count());
        }
        else
        {
            std::cout << "Sensor 'Sensor0' introuvable → test ignoré." << std::endl;
            results.push_back(-1);
        }
    } catch (...) {
        std::cout << "Erreur lors de compareSensors()" << std::endl;
        results.push_back(-1);
    }

    // 5. extrapolateAQI
    try {
        t1 = std::chrono::high_resolution_clock::now();
        auto extrapolated = stats.extrapolateAQI(44.8, 1.8, start, end, 2000);
        t2 = std::chrono::high_resolution_clock::now();
        auto duration5 = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << "extrapolateAQI() : " << duration5.count() << " ms (" << extrapolated.size() << " extrapolations)" << std::endl;
        results.push_back(duration5.count());
    } catch (...) {
        std::cout << "Erreur lors de extrapolateAQI()" << std::endl;
        results.push_back(-1);
    }

    std::cout << "=== Fin de l'évaluation ===" << std::endl;
    return results;
}

//------------------------------------------------- Surcharge d'opérateurs
AdminServices& AdminServices::operator = (const AdminServices& unAdminServices)
// Algorithme :
//
{
    if (this != &unAdminServices) 
    {
        uda = unAdminServices.uda;
        sensors = unAdminServices.sensors;
    }

    return *this; 
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AdminServices::AdminServices( const AdminServices & unAdminServices )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AdminServices>" << endl;
#endif
    uda = unAdminServices.uda;
    sensors = unAdminServices.sensors;
    authService = unAdminServices.authService;
} //----- Fin de AdminServices (constructeur de copie)

AdminServices::AdminServices ( UserDataAccess p_uda, vector<Sensor>* p_sensors, AuthService* p_authService )
// Algorithme :
//
: uda(p_uda), sensors(p_sensors), authService(p_authService)
{
#ifdef MAP
    cout << "Appel au constructeur de <AdminServices>" << endl;
#endif
} //----- Fin de AdminServices

AdminServices::~AdminServices ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AdminServices>" << endl;
#endif
} //----- Fin de ~AdminServices


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
