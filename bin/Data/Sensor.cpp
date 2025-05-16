/*************************************************************************
Sensor  -  todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//------- Réalisation de la classe <Sensor> (fichier Sensor.cpp) ---------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double Sensor::distanceTo(double lat, double lng)
{
}
// Algorithme :
//
//{
//} //----- Fin de distanceTo

list<Sensor> Sensor::getSensorNeighbours()
{
}
// Algorithme :
//
//{
//} //----- Fin de getSensorNeighbours

list<list<Measurement>> Sensor::getMeasurements(time_t period_start, time_t period_end)
{
}
// Algorithme :
//
//{
//} //----- Fin de getMeasurements

list<Measurement> Sensor::getClosestMeasurements(time_t instant, int before_after)
{
}
// Algorithme :
//
//{
//} //----- Fin de getClosestMeasurements


//------------------------------------------------- Surcharge d'opérateurs
Sensor& Sensor::operator = ( const Sensor& unSensor )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor ( const Sensor & unSensor )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Sensor>" << endl;
#endif
} //----- Fin de Sensor (constructeur de copie)


Sensor::Sensor ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
} //----- Fin de Sensor


Sensor::~Sensor ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Sensor>" << endl;
#endif
} //----- Fin de ~Sensor


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées