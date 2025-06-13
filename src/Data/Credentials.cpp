/*************************************************************************
Credentials  -  Objet métier stockant les informations des Cleaners
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


// ---------------------------------------------------- Getters / Setters
string Credentials::getLogin ( ) const
// Algorithme :
//
{
    return login;
} //----- Fin de getLogin

string Credentials::getPassword ( ) const
// Algorithme :
//
{
    return password;
} //----- Fin de getPassword

UserType Credentials::getUserType ( ) const
// Algorithme :
//
{
    return userType;
} //----- Fin de getUserType

string Credentials::getUserId ( ) const
// Algorithme :
//
{
    return userId;
} //----- Fin de getUserId


//------------------------------------------------- Surcharge d'opérateurs
Credentials& Credentials::operator = ( const Credentials& unCredentials )
// Algorithme :
//
{
    if (this != &unCredentials)
    {
        this->login = unCredentials.login;
        this->password = unCredentials.password;
        this->userType = unCredentials.userType;
        this->userId = unCredentials.userId;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Credentials::Credentials ( const Credentials & unCredentials )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Credentials>" << endl;
#endif
    this->login = unCredentials.login;
    this->password = unCredentials.password;
    this->userType = unCredentials.userType;
    this->userId = unCredentials.userId;
} //----- Fin de Credentials (constructeur de copie)

Credentials::Credentials ( string p_login, string p_password, UserType p_userType, string p_userId )
// Algorithme :
//
: login(p_login), password(p_password), userType(p_userType), userId(p_userId)
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

