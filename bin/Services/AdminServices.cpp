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
