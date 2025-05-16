/*************************************************************************
UserDataAccess  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <UserDataAccess> (fichier UserDataAccess.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "UserDataAccess.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int UserDataAccess::loadUserPoints(string userId)
{
}
// Algorithme :
//
//{
//} //----- Fin de loadUserPoints

int UserDataAccess::updateUserPoints(string userId)
{
}
// Algorithme :
//
//{
//} //----- Fin de updateUserPoints

list<string> UserDataAccess::loadExcludedUsers()
{
}
// Algorithme :
//
//{
//} //----- Fin de loadExcludedUsers

int UserDataAccess::addExcludedUser(string userId)
{
}
// Algorithme :
//
//{
//} //----- Fin de addExcludedUser


//------------------------------------------------- Surcharge d'opérateurs
UserDataAccess& UserDataAccess::operator = ( const UserDataAccess& unUserDataAccess )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
UserDataAccess::UserDataAccess ( const UserDataAccess & unUserDataAccess )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <UserDataAccess>" << endl;
#endif
} //----- Fin de UserDataAccess (constructeur de copie)


UserDataAccess::UserDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UserDataAccess>" << endl;
#endif
} //----- Fin de UserDataAccess


UserDataAccess::~UserDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UserDataAccess>" << endl;
#endif
} //----- Fin de ~UserDataAccess


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
