/*************************************************************************
services_tests  -  tests unitaires des méthodes de la couche services
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <services_tests> (fichier services_tests.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Services_Tests.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Services_Tests::runTests()
{
    // Implémentez ici les tests unitaires pour les méthodes de la couche Services
    cout << "Running services tests..." << endl;

    // Exemple de test
    // assert(serviceMethod() == expectedValue);

    cout << "Services tests completed." << endl;
} //----- Fin de runTests

//-------------------------------------------- Constructeurs - destructeur
services_tests::services_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <services_tests>" << endl;
#endif
} //----- Fin de services_tests

services_tests::~services_tests( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <services_tests>" << endl;
#endif
} //----- Fin de ~services_tests

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
