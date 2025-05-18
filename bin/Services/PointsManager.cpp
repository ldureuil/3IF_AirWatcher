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
bool PointsManager::award(const vector<string>& sensorsUsed)
//Algotithme :
{
    UserDataAccess userDataAccess;
    // Iteración con iterador explícito
    for (vector<string>::const_iterator sensorIt = sensorsUsed.begin(); 
         sensorIt != sensorsUsed.end(); 
         ++sensorIt) {
        
        // Buscar el sensor en la colección
        vector<Sensor>::iterator sensorFound = find_if( sensors->begin(), sensors->end(),
            [&](const Sensor& s) { return s.getId() == *sensorIt; });
        
        if (sensorFound != sensors->end()) {
            const string& userSensorId = sensorFound->getUserId();
            userDataAccess.updateUserPoints(userSensorId);
        }
    }
    
    return true; // O algún valor que indique éxito/fracaso

} //----- Fin de award

int PointsManager::getPoints(string userId)
// Algorithme :
{
    UserDataAccess userDataAccess;
    int points = userDataAccess.loadUserPoints(userId);
    return points;
}//----- Fin de getPoints


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


PointsManager::PointsManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <PointsManager>" << endl;
#endif
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
