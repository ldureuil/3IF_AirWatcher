/*************************************************************************
Credentials  -  todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//--- Réalisation de la classe <Credentials> (fichier Credentials.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Credentials.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


//------------------------------------------------- Surcharge d'opérateurs
Credentials& Credentials::operator = ( const Credentials& unCredentials )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Credentials::Credentials ( const Credentials & unCredentials )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Credentials>" << endl;
#endif
} //----- Fin de Credentials (constructeur de copie)


Credentials::Credentials ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Credentials>" << endl;
#endif
} //----- Fin de Credentials


Credentials::~Credentials ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Credentials>" << endl;
#endif
} //----- Fin de ~Credentials


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

