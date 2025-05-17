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


//------------------------------------------------- Surcharge d'opérateurs
ParticulierData& ParticulierData::operator = ( const ParticulierData& unParticulierData )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
ParticulierData::ParticulierData( const ParticulierData & unParticulierData )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <ParticulierData>" << endl;
#endif
} //----- Fin de ParticulierData (constructeur de copie)


ParticulierData::ParticulierData( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <ParticulierData>" << endl;
#endif
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

