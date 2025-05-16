/*************************************************************************
Measurement  -  todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//--- Réalisation de la classe <Measurement> (fichier Measurement.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool Measurement::isWithin(time_t period_start, time_t period_end)
{
}
// Algorithme :
//
//{
//} //----- Fin de isWithin


//------------------------------------------------- Surcharge d'opérateurs
Measurement& Measurement::operator = ( const Measurement& unMeasurement )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement ( const Measurement & unMeasurement )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Measurement>" << endl;
#endif
} //----- Fin de Measurement (constructeur de copie)


Measurement::Measurement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Measurement>" << endl;
#endif
} //----- Fin de Measurement


Measurement::~Measurement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Measurement>" << endl;
#endif
} //----- Fin de ~Measurement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées