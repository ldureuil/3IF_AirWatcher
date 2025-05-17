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
vector<Sensor> Cleaner::getNeighbouringSensors( int radius, vector<Sensor> *sensors )
// Algorithme :
//
{
    vector<Sensor> neighbours;
    for ( vector<Sensor>::iterator sensor_it = sensors->begin() ; sensor_it != sensors->end() ; ++sensor_it )
    {
        if (sensor_it->distanceTo ( this->lat, this->lng ) < radius)
        {
            neighbours.push_back(*sensor_it);
        }
    }
    return neighbours;
} //----- Fin de getNeighbouringSensors

string Cleaner::getId ( )
{
    return this->id;
}

double Cleaner::getLat ( )
{
    return this->lat;
}

double Cleaner::getLng ( )
{
    return this->lng;
}

time_t Cleaner::getStart ( )
{
    return this->start;
}

time_t Cleaner::getEnd ( )
{
    return this->end;
}

//------------------------------------------------- Surcharge d'opérateurs
Cleaner& Cleaner::operator = ( const Cleaner& unCleaner )
// Algorithme :
//
{
    if (this != &unCleaner)
    {
        this->id = unCleaner.id;
        this->lat = unCleaner.lat;
        this->lng = unCleaner.lng;
        this->start = unCleaner.start;
        this->end = unCleaner.end;
    }
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Cleaner::Cleaner ( const Cleaner & unCleaner )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Cleaner>" << endl;
#endif
    this->id = unCleaner.id;
    this->lat = unCleaner.lat;
    this->lng = unCleaner.lng;
    this->start = unCleaner.start;
    this->end = unCleaner.end;
} //----- Fin de Cleaner (constructeur de copie)


Cleaner::Cleaner ( string p_id, double p_lat, double p_lng, time_t p_start, time_t p_end ) 
    : id(p_id), lat(p_lat), lng(p_lng), start(p_start), end(p_end)
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
