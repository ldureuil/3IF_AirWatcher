/*************************************************************************
PointsManager  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <PointsManager> (fichier PointsManager.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <algorithm>
#include <unordered_set>

//------------------------------------------------------ Include personnel
#include "PointsManager.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool PointsManager::award(const vector<string>& sensorsUsed)
//Algotithme : iter sur chaque capteur utilisé
// et vérifier s'il est connu
// Si le capteur est trouvé, on met à jour les points de l'utilisateur
// Sinon, on le signale
// On vérifie si l'utilisateur est exclu
// On vérifie si l'utilisateur a déjà été traité
// On ajoute l'utilisateur à la liste des utilisateurs traités
// On retourne un booléen indiquant si tous les capteurs sont connus
{
    bool capteursConnus=true;
    UserDataAccess userDataAccess;
    unordered_set<string> users;
    vector<string> excludedUsers = userDataAccess.loadExcludedUsers();
    unordered_set<string> excludedUsersSet(excludedUsers.begin(),
                                           excludedUsers.end());

    // On itere sur chaque capteur utilisé
    for (vector<string>::const_iterator sensorIt = sensorsUsed.begin(); 
         sensorIt != sensorsUsed.end(); 
         ++sensorIt) {
        // On cherche le capteur dans la collection de capteurs
        vector<Sensor>::iterator sensorFound = find_if( sensors->begin(), sensors->end(),
            [&](Sensor& s) { return s.getId() == *sensorIt; });
        
        // Si le capteur n'est pas trouvé, on le signale
        if (sensorFound == sensors->end()) {
            capteursConnus = false;
            continue; // Salta al siguiente sensor
        }

        // Si le capteur est trouvé, on met à jour les points de l'utilisateur
        const string& userSensorId = sensorFound->getUserId();
        // On vérifie si l'utilisateur est exclu
        if(excludedUsersSet.find(userSensorId) != excludedUsersSet.end()) {
            capteursConnus = false;
            continue; // Salta al siguiente sensor
        }
        // On vérifie si l'utilisateur a déjà été traité
        if(users.find(userSensorId) == users.end()) {
            userDataAccess.updateUserPoints(userSensorId);
        }
        // On ajoute l'utilisateur à la liste des utilisateurs traités
        users.insert(userSensorId);
    }
    
    return capteursConnus;


} //----- Fin de award

int PointsManager::getPoints( string userId )
// Algorithme :
//
{
    if (userId == "")
    {
        cerr << "Erreur : l'utilisateur n'est pas spécifié." << endl;
        return -1; // Si l'utilisateur n'est pas spécifié, erreur
    }

    // On vérifie si l'utilisateur existe
    for (auto& sensor : *sensors)
	{
        if (sensor.getUserId() == userId)
		{
            // On vérifie si l'utilisateur existe
        	if (userId != "")
        	{
                for (ParticulierData& particulier : *(this->particulierData))
                {
                    if (particulier.getId() == userId)
                    {
                        // On a trouvé l'utilisateur
                        int points = particulier.getPoints();

                        return points;
                    }
                }
        	}
        }
    }

    cerr << "Erreur : l'utilisateur n'existe pas." << endl;
    return -1;

} //----- Fin de getPoints

vector<Sensor>* PointsManager::getSensors(void)
// Algorithme :
{
    return this->sensors;
}

void PointsManager::setSensors(vector<Sensor>* sensors)
// Algorithme :
// 
{ this->sensors = sensors; } //----- Fin de setSensors

//------------------------------------------------- Surcharge d'opérateurs
PointsManager& PointsManager::operator = ( const PointsManager& unPointsManager )
// Algorithme :
//
{
    if (this != &unPointsManager)
    {
        uda = unPointsManager.uda;
        particulierData = unPointsManager.particulierData; // copie simplement le pointeur
        sensors = unPointsManager.sensors;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
PointsManager::PointsManager( const PointsManager& unPointsManager )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <PointsManager>" << endl;
#endif
    uda = unPointsManager.uda;
    particulierData = unPointsManager.particulierData; // copie simplement le pointeur
    sensors = unPointsManager.sensors;
} //----- Fin de PointsManager (constructeur de copie)

PointsManager::PointsManager( UserDataAccess p_uda, vector<ParticulierData>* p_particulierData, vector<Sensor>* p_sensors )
// Algorithme :
//
: uda(p_uda), particulierData(p_particulierData), sensors(p_sensors)
{
#ifdef MAP
    cout << "Appel au constructeur de <PointsManager>" << endl;
#endif
    this->sensors = sensors;
} //----- Fin de PointsManager


PointsManager::~PointsManager( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PointsManager>" << endl;
#endif
} //----- Fin de ~PointsManager


//------------------------------------------------------------------ PRIVE


//----------------------------------------------------- Méthodes protégées
