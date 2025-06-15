/*************************************************************************
unit_tests_main  -  Point d'entrée pour les tests unitaires
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "unit_tests/dataLoader_tests.h"
#include "unit_tests/data_tests.h"
#include "unit_tests/services_tests.h"

int main() {
    cout << "====== Lancement des tests unitaires ======" << endl;

    int nbTestsOk = 0;

    // Tests de la couche Services
    services_tests sTests;
    nbTestsOk += sTests.runTests();

    // Tests de la couche Data
    data_tests dTests;
    nbTestsOk += dTests.runTests();

    // Tests de la couche DataLoader
    dataLoader_tests dlTests;
    nbTestsOk += dlTests.runTests();

    cout << "Nombre de tests réussis : " << nbTestsOk << " / 62 tests implémentés" << endl;

    cout << "====== Fin des tests unitaires ======" << endl;
    return 0;
}