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
//#include "unit_tests/data_tests.h"
//#include "unit_tests/services_tests.h"

int main() {
    cout << "====== Lancement des tests unitaires ======" << endl;

    // Tests de la couche DataLoader
    dataLoader_tests dlTests;
    dlTests.runTests();

    // Ajouter ici les autres tests unitaires

    cout << "====== Fin des tests unitaires ======" << endl;
    return 0;
}