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

//------------------------------------------------------ Include personnel
#include "PointsManager.h"
#include <algorithm>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
#include <unordered_set>

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


int PointsManager::getPoints(string userId)
// Algorithme : faire appel à la classe UserDataAccess
// et à la méthode loadUserPoints
{
    UserDataAccess userDataAccess;
    int points = userDataAccess.loadUserPoints(userId);
    return points;
}//----- Fin de getPoints

void PointsManager::setSensors(vector<Sensor>* sensors)
// Algorithme :
// 
{ this->sensors = sensors; } //----- Fin de setSensors

vector<Sensor>* PointsManager::getSensors(void)
// Algorithme :
{
    return this->sensors;
}


//------------------------------------------------- Surcharge d'opérateurs
PointsManager& PointsManager::operator = ( const PointsManager& unPointsManager )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
PointsManager::PointsManager ( const PointsManager & unPointsManager )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <PointsManager>" << endl;
#endif
} //----- Fin de PointsManager (constructeur de copie)


PointsManager::PointsManager (vector<Sensor>* sensors)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <PointsManager>" << endl;
#endif
    this->sensors = sensors;
} //----- Fin de PointsManager


PointsManager::~PointsManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PointsManager>" << endl;
#endif
} //----- Fin de ~PointsManager


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
