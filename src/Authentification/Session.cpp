/*************************************************************************
Session  -  Classe de gestion des sessions utilisateur
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//------ Réalisation de la classe <Session> (fichier Session.cpp) --------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Session.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
UserType Session::getUserType ( ) const
// Algorithme :
//
{
    return userType;
} //----- Fin de getUserType

string Session::getUserId ( ) const
// Algorithme :
//
{
    return userId;
} //----- Fin de getUserId


//------------------------------------------------- Surcharge d'opérateurs
Session& Session::operator = ( const Session& unSession )
// Algorithme :
//
{
    if (this != &unSession)
    {
        this->userType = unSession.userType;
        this->userId = unSession.userId;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Session::Session ( const Session & unSession )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Session>" << endl;
#endif
    this->userType = unSession.userType;
    this->userId = unSession.userId;
} //----- Fin de Session (constructeur de copie)

Session::Session ( )
// Algorithme : Initialisation par défaut
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Session>" << endl;
#endif
    this->userType = UNDEFINED;
    this->userId = "";
} //----- Fin de Session

Session::Session ( UserType p_userType, string p_userId )
// Algorithme :
//
: userType(p_userType), userId(p_userId)
{
#ifdef MAP
    cout << "Appel au constructeur de <Session>" << endl;
#endif
} //----- Fin de Session

Session::~Session ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Session>" << endl;
#endif
} //----- Fin de ~Session


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
