/*************************************************************************
AuthService  -  todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//--- Réalisation de la classe <AuthService> (fichier AuthService.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AuthService.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
Session AuthService::login(string login, string password)
{
}
// Algorithme :
//
//{
//} //----- Fin de login

bool AuthService::checkRequiredRole(Session session, UserType role)
{
}
// Algorithme :
//
//{
//} //----- Fin de checkRequiredRole


//------------------------------------------------- Surcharge d'opérateurs
AuthService& AuthService::operator = ( const AuthService& unAuthService )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AuthService::AuthService ( const AuthService & unAuthService )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AuthService>" << endl;
#endif
} //----- Fin de AuthService (constructeur de copie)


AuthService::AuthService ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AuthService>" << endl;
#endif
} //----- Fin de AuthService


AuthService::~AuthService ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AuthService>" << endl;
#endif
} //----- Fin de ~AuthService


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
