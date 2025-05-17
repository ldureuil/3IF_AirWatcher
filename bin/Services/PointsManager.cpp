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
#include <unordered_set>
#include <vector>

//------------------------------------------------------ Include personnel
#include "PointsManager.h"
#include "../DataAccess/UserDataAccess.h"
#include "../DataAccess/DataLoader.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool PointsManager::award(vector<string> sensorsUsed)
{
    
    
    bool updated = 0; 
    
    for (auto& sensorId : sensorsUsed) {
        Sensor * sensor = dl.getSensor(sensorId);
        string userId = sensor->getUserId();

        if (&userId != nullptr)
        {
            uda.updateUserPoints(userId);
            updated = 1;
        }
        
    }

    return updated; // Retourne vrai s'il y a eu au moins une mise à jour
}
    
    
// Algorithme :
//
//{
//} //----- Fin de award

int PointsManager::getPoints(string userId)
{
    
    int points = uda.loadUserPoints(userId);

}
// Algorithme :
//
//{
//} //----- Fin de getPoints


//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

PointsManager::PointsManager (  UserDataAccess Uda , DataLoader dataloader)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <PointsManager>" << endl;
#endif

    UserDataAccess uda =Uda;
    DataLoader dl = dataloader;
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
