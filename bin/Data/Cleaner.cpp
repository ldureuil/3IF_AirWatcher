/*************************************************************************
Cleaner  -  todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//------ Réalisation de la classe <Cleaner> (fichier Cleaner.cpp) --------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Cleaner.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
list<Sensor> Cleaner::getNeighbouringSensors(int radius)
{
}
// Algorithme :
//
//{
//} //----- Fin de getNeighbouringSensors


//------------------------------------------------- Surcharge d'opérateurs
Cleaner& Cleaner::operator = ( const Cleaner& unCleaner )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner ( const Cleaner & unCleaner )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner (constructeur de copie)


Cleaner::Cleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner


Cleaner::~Cleaner ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
