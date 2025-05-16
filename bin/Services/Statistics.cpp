/*************************************************************************
Statistics  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---- Réalisation de la classe <Statistics> (fichier Statistics.cpp) ----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Statistics.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Statistics::analyzeSensor(string sensorId)
{
}
// Algorithme :
//
//{
//} //----- Fin de analyzeSensor

list<int> Statistics::analyzeCleaner(string cleanerId)
{
}
// Algorithme :
//
//{
//} //----- Fin de analyzeCleaner

list<Measurement> Statistics::computeZone(double lat, double lng, time_t period_start, time_t period_end, int radius)
{
}
// Algorithme :
//
//{
//} //----- Fin de computeZone

list<Sensor> Statistics::compareSensors(string sensorId, time_t period_start, time_t period_end)
{
}
// Algorithme :
//
//{
//} //----- Fin de compareSensors

list<Measurement> Statistics::extrapolateAQI(double lat, double lng, time_t period_start, time_t period_end)
{
}
// Algorithme :
//
//{
//} //----- Fin de extrapolateAQI


//------------------------------------------------- Surcharge d'opérateurs
Statistics& Statistics::operator = ( const Statistics& unStatistics )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Statistics::Statistics ( const Statistics & unStatistics )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Statistics>" << endl;
#endif
} //----- Fin de Statistics (constructeur de copie)


Statistics::Statistics ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Statistics>" << endl;
#endif
} //----- Fin de Statistics


Statistics::~Statistics ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Statistics>" << endl;
#endif
} //----- Fin de ~Statistics


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
