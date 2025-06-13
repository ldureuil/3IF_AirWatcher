/*************************************************************************
dataLoader_tests  -  tests unitaires des méthodes de la couche DataLoader
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <dataLoader_tests> (fichier dataLoader_tests.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "dataLoader_tests.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

//-------------------------------------------- Constructeurs - destructeur
dataLoader_tests::dataLoader_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <dataLoader_tests>" << endl;
#endif
} //----- Fin de dataLoader_tests

dataLoader_tests::~dataLoader_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <dataLoader_tests>" << endl;
#endif
} //----- Fin de ~dataLoader_tests

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
