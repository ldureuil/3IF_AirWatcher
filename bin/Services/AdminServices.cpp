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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool AdminServices::excludeSensor( string sensorId )
// Algorithme :
//
{
    bool exist = false;
    Sensor* sensorExclu; 
    for ( auto sensor : *sensors )
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
    uda.addExcludedUser(userId);

    return true;
} //----- Fin de excludeSensor


void  AdminServices::evaluate(Statistics stats)
// Algorithme :
//
{
    using namespace std::chrono;
    cout << "\n=== Évaluation des performances des méthodes de Statistics ===\n";

    time_t now = time(nullptr);
    time_t before = now - 3600; // 1 heure avant

    // Méthode 1 : computeZone
    auto t1 = high_resolution_clock::now();
    auto res1 = stats.computeZone(45.75, 4.85, before, now, 1000, 2000);
    auto t2 = high_resolution_clock::now();
    cout << "computeZone() : " << duration_cast<milliseconds>(t2 - t1).count() << " ms (" << res1.size() << " mesures)\n";

    // Méthode 2 : analyzeCleaner
    vector<Measurement> cleaners;

    if (stats.getCleanerByID("Cleaner1") != nullptr)
    {
        cleaners = stats.analyzeCleaner("Cleaner1", 1000);
    }
    else
    {
        cout << "Cleaner 'Cleaner1' introuvable." << endl;
    }
    auto t3 = high_resolution_clock::now();
    cout << "analyzeCleaner() : " << duration_cast<milliseconds>(t3 - t2).count() << " ms (" << cleaners.size() << " mesures)\n";

    // Méthode 3 : analyzeSensor
    t1 = high_resolution_clock::now();
    int result = stats.analyzeSensor("Sensor-001");
    t2 = high_resolution_clock::now();
    cout << "analyzeSensor() : " << duration_cast<milliseconds>(t2 - t1).count() << " ms (résultat : " << result << ")\n";

    // Méthode 4 : compareSensors
    t1 = high_resolution_clock::now();
    auto sensors = stats.compareSensors("Sensor-001", before, now);
    t2 = high_resolution_clock::now();
    cout << "compareSensors() : " << duration_cast<milliseconds>(t2 - t1).count() << " ms (" << sensors.size() << " capteurs)\n";

    // Méthode 5 : extrapolateAQI
    t1 = high_resolution_clock::now();
    auto aqi = stats.extrapolateAQI(45.75, 4.85, before, now, 2000);
    t2 = high_resolution_clock::now();
    cout << "extrapolateAQI() : " << duration_cast<milliseconds>(t2 - t1).count() << " ms (" << aqi.size() << " extrapolations)\n";

    cout << "=== Fin de l'évaluation ===\n\n";

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
} //----- Fin de AdminServices (constructeur de copie)

AdminServices::AdminServices ( UserDataAccess p_uda, vector<Sensor>* p_sensors )
// Algorithme :
//
: uda(p_uda), sensors(p_sensors)
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
