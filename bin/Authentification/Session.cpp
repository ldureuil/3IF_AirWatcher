/*************************************************************************
Session  -  todo
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


//------------------------------------------------- Surcharge d'opérateurs
Session& Session::operator = ( const Session& unSession )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Session::Session ( const Session & unSession )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Session>" << endl;
#endif
} //----- Fin de Session (constructeur de copie)


Session::Session ( )
// Algorithme :
//
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
