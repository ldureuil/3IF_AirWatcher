/*************************************************************************
ParticulierData  -  todo
                             -------------------
    début                : 17/05/2025
*************************************************************************/

//- Réalisation de la classe <ParticulierData> (fichier ParticulierData.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "ParticulierData.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


// ---------------------------------------------------- Getters / Setters
string ParticulierData::getId()
// Algorithme :
// Renvoie l'identifiant du particulier
{
    return id;
} //----- Fin de getId

int ParticulierData::getPoints()
// Algorithme :
// Renvoie le nombre de points du particulier
{
    return points;
} //----- Fin de getPoints

bool ParticulierData::getIsExcluded()
// Algorithme :
// Renvoie si le particulier est exclu
{
    return isExcluded;
} //----- Fin de getIsExcluded

bool ParticulierData::setId(string p_id)
// Algorithme :
// Modifie l'identifiant du particulier
{
    id = p_id;
    return true;
} //----- Fin de setId

bool ParticulierData::setPoints(int p_points)
// Algorithme :
// Modifie le nombre de points du particulier
{
    points = p_points;
    return true;
} //----- Fin de setPoints

bool ParticulierData::setIsExcluded(bool p_isExcluded)
// Algorithme :
// Modifie si le particulier est exclu
{
    isExcluded = p_isExcluded;
    return true;
} //----- Fin de setIsExcluded


//------------------------------------------------- Surcharge d'opérateurs
ParticulierData& ParticulierData::operator = ( const ParticulierData& unParticulierData )
// Algorithme :
//
{
    if (this != &unParticulierData) {
        id = unParticulierData.id;
        points = unParticulierData.points;
        isExcluded = unParticulierData.isExcluded;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
ParticulierData::ParticulierData( const ParticulierData & unParticulierData )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ParticulierData>" << endl;
#endif
    id = unParticulierData.id;
    points = unParticulierData.points;
    isExcluded = unParticulierData.isExcluded;
} //----- Fin de ParticulierData (constructeur de copie)

ParticulierData::ParticulierData( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ParticulierData>" << endl;
#endif
} //----- Fin de ParticulierData

ParticulierData::ParticulierData( string p_id, int p_points, bool p_isExcluded )
// Algorithme :
//
: id(p_id), points(p_points), isExcluded(p_isExcluded)
{
#ifdef MAP
    cout << "Appel au constructeur de <ParticulierData>" << endl;
# endif
} //----- Fin de ParticulierData

ParticulierData::~ParticulierData( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <ParticulierData>" << endl;
#endif
} //----- Fin de ~ParticulierData


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

