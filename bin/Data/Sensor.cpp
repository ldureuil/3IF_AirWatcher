/*************************************************************************
Sensor  -  Objet métier stockant les informations d'un capteur
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
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double Sensor::distanceTo( double lat2, double lng2 )
// Algorithme :
//
{
    // Distance euclidienne simple
    double dLat = lat - lat2;
    double dLng = lng - lng2;

    return sqrt(dLat * dLat + dLng * dLng);
} //----- Fin de distanceTo

vector<Sensor> Sensor::getSensorNeighbours( vector<Sensor>* sensors, int radius )
// Algorithme :
//
{
    vector<Sensor> nearby_sensors;
    int distance = 0;
    for (auto& s : *sensors)
    {
        distance = distanceTo(s.getLat(), s.getLng());
        if (distance <= radius)
        {
            nearby_sensors.push_back(s);
        }
    }
    return nearby_sensors;
} //----- Fin de getSensorNeighbours

vector<Measurement> Sensor::getMeasurements( time_t period_start, time_t period_end )
// Algorithme :
//
{
    vector<Measurement> result;
    for (auto& m : measurements)
    {

        if (m.getTs()>= period_start && m.getTs() <= period_end)
        {
            result.push_back(m);
        }
    }

    return result;
} //----- Fin de getMeasurements

vector<Measurement> Sensor::getClosestMeasurements( time_t instant, int before_after )
// Algorithme :
//
{
    vector<Measurement> filtered;

    for (Measurement m : measurements)
    {
        time_t ts = m.getTs();

        // Avant l'instant (-1)
        if (before_after == -1 && ts < instant)
        {
            filtered.push_back(m);
        }
        // Après l'instant (+1)
        else if (before_after == 1 && ts > instant)
        {
            filtered.push_back(m);
        }
    }

    return filtered;
} //----- Fin de getClosestMeasurements


// ---------------------------------------------------- Getters / Setters
string Sensor::getId( )
// Algorithme :
//
{
    return id;
} //----- Fin de getId

double Sensor::getLat( )
// Algorithme :
//
{
    return lat;
} //----- Fin de getLat

double Sensor::getLng( )
// Algorithme :
//
{
    return lng;
} //----- Fin de getLng

string Sensor::getUserId( )
// Algorithme :
//
{
    return userId;
} //----- Fin de getUserId

vector<Measurement> Sensor::getAllMeasurements( )
// Algorithme :
//
{
    return measurements;
} //----- Fin de getAllMeasurements

bool Sensor::setId( string p_id )
// Algorithme :
//
{
    id = p_id;
    return true;
} //----- Fin de setId

bool Sensor::setLat( double p_lat )
// Algorithme :
//
{
    lat = p_lat;
    return true;
} //----- Fin de setLat

bool Sensor::setLng( double p_lng )
// Algorithme :
//
{
    lng = p_lng;
    return true;
} //----- Fin de setLng

bool Sensor::setMeasurements( vector<Measurement> p_measurements )
// Algorithme :
//
{
    measurements = p_measurements;
    return true;
} //----- Fin de setMeasurements

bool Sensor::setUserId( string p_userId )
// Algorithme :
//
{
    userId = p_userId;
    return true;
} //----- Fin de setUserId


//------------------------------------------------- Surcharge d'opérateurs
Sensor& Sensor::operator = ( const Sensor& unSensor )
// Algorithme :
//
{
    if (this != &unSensor)
    {
        id = unSensor.id;
        lat = unSensor.lat;
        lng = unSensor.lng;
        measurements = unSensor.measurements;
        userId = unSensor.userId;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Sensor::Sensor( const Sensor & unSensor )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Sensor>" << endl;
#endif
    id = unSensor.id;
    lat = unSensor.lat;
    lng = unSensor.lng;
    measurements = unSensor.measurements;
    userId = unSensor.userId;
} //----- Fin de Sensor (constructeur de copie)

Sensor::Sensor( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Sensor>" << endl;
#endif
    id = "";
    lat = 0;
    lng = 0;
    userId = "";
    measurements = vector<Measurement>();
} //----- Fin de Sensor

Sensor::Sensor( string p_id, double p_lat, double p_lng, vector<Measurement> p_measurements, string p_userId )
// Algorithme :
//
: id(p_id), lat(p_lat), lng(p_lng), measurements(p_measurements), userId(p_userId)
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