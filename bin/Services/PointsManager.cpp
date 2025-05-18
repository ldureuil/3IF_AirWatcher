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
#include <unordered_set>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool PointsManager::award( vector<string> sensorsUsed )
// Algorithme :
//
{
    bool updated = 0; 

    for (auto& sensorId : sensorsUsed)
	{
	    for (auto& sensor : *sensors)
	    {
            if (sensor->getId() == sensorId)
			{
                // On a trouvé le capteur correspondant
                // On peut mettre à jour les points de l'utilisateur
                string userId = sensor->getUserId();

                // On vérifie si l'utilisateur existe
        		if (&userId != "")
        		{
            		uda.updateUserPoints(userId);
            		updated = 1;
        		}
				break; // On sort de la boucle une fois qu'on a trouvé le capteur
            }
        }
    }

    return updated; // Retourne vrai s'il y a eu au moins une mise à jour
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
        if (sensor->getUserId() == userId)
		{
            // On vérifie si l'utilisateur existe
        	if (&userId != "")
        	{
                for (auto& particulier : particulierData)
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

PointsManager::PointsManager( UserDataAccess p_uda, vector<ParticulierData> p_particulierData, vector<Sensor>* p_sensors )
// Algorithme :
//
: uda(p_uda), particulierData(p_particulierData), sensors(p_sensors)
{
#ifdef MAP
    cout << "Appel au constructeur de <PointsManager>" << endl;
#endif
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
