/*************************************************************************
Cleaner  -  Objet métier stockant les informations des Cleaners
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
vector<Sensor> Cleaner::getNeighbouringSensors( int radius, vector<Sensor>* sensors )
// Algorithme :
//
{
    vector<Sensor> neighbours;
    for (vector<Sensor>::iterator sensor_it = sensors->begin(); sensor_it != sensors->end(); sensor_it++)
    {
        if (sensor_it->distanceTo(lat, lng) < radius)
        {
            neighbours.push_back(*sensor_it);
        }
    }
    return neighbours;
} //----- Fin de getNeighbouringSensors


// ---------------------------------------------------- Getters / Setters
string Cleaner::getId( )
// Algorithme :
//
{
    return id;
} //----- Fin de getId

double Cleaner::getLat( )
// Algorithme :
//
{
    return lat;
} //----- Fin de getLat

double Cleaner::getLng( )
// Algorithme :
//
{
    return lng;
} //----- Fin de getLng

time_t Cleaner::getStart( )
// Algorithme :
//
{
    return start;
} //----- Fin de getStart

time_t Cleaner::getEnd( )
// Algorithme :
//
{
    return end;
} //----- Fin de getEnd


//------------------------------------------------- Surcharge d'opérateurs
Cleaner& Cleaner::operator = ( const Cleaner& unCleaner )
// Algorithme :
//
{
    if (this != &unCleaner)
    {
        id = unCleaner.id;
        lat = unCleaner.lat;
        lng = unCleaner.lng;
        start = unCleaner.start;
        end = unCleaner.end;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner( const Cleaner & unCleaner )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Cleaner>" << endl;
#endif
    id = unCleaner.id;
    lat = unCleaner.lat;
    lng = unCleaner.lng;
    start = unCleaner.start;
    end = unCleaner.end;
} //----- Fin de Cleaner (constructeur de copie)

Cleaner::Cleaner( string p_id, double p_lat, double p_lng, time_t p_start, time_t p_end )
// Algorithme :
//
: id(p_id), lat(p_lat), lng(p_lng), start(p_start), end(p_end)
{
#ifdef MAP
    cout << "Appel au constructeur de <Cleaner>" << endl;
#endif
} //----- Fin de Cleaner

Cleaner::~Cleaner( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Cleaner>" << endl;
#endif
} //----- Fin de ~Cleaner


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
