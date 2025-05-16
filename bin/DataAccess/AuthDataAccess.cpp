/*************************************************************************
AuthDataAccess  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <AuthDataAccess> (fichier AuthDataAccess.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AuthDataAccess.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
list<Credentials> AuthDataAccess::loadCredentials()
{
}
// Algorithme :
//
//{
//} //----- Fin de loadCredentials

Credentials AuthDataAccess::findCredentials()
{
}
// Algorithme :
//
//{
//} //----- Fin de findCredentials


//------------------------------------------------- Surcharge d'opérateurs
AuthDataAccess& AuthDataAccess::operator = ( const AuthDataAccess& unAuthDataAccess )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AuthDataAccess::AuthDataAccess ( const AuthDataAccess & unAuthDataAccess )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AuthDataAccess>" << endl;
#endif
} //----- Fin de AuthDataAccess (constructeur de copie)


AuthDataAccess::AuthDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AuthDataAccess>" << endl;
#endif
} //----- Fin de AuthDataAccess


AuthDataAccess::~AuthDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AuthDataAccess>" << endl;
#endif
} //----- Fin de ~AuthDataAccess


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
