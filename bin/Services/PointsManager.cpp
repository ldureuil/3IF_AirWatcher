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

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool PointsManager::award(list<string> sensorsUsed)
{
}
// Algorithme :
//
//{
//} //----- Fin de award

int PointsManager::getPoints(string userId)
{
}
// Algorithme :
//
//{
//} //----- Fin de getPoints


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
