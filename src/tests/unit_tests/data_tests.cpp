/*************************************************************************
data_tests  -  tests unitaires des méthodes de la couche Data
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---- Réalisation de la classe <data_tests> (fichier data_tests.cpp) ----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "data_tests.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void data_tests::runTests()
{
    // Implémentez ici les tests unitaires pour les méthodes de la couche Data
    cout << "Running data tests..." << endl;

    // Exemple de test
    // assert(dataMethod() == expectedValue);

    cout << "Data tests completed." << endl;
} //----- Fin de runTests

//-------------------------------------------- Constructeurs - destructeur
data_tests::data_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <data_tests>" << endl;
#endif
} //----- Fin de data_tests

data_tests::~data_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <data_tests>" << endl;
#endif
} //----- Fin de ~data_tests

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
