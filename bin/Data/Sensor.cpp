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
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
double Sensor::distanceTo(double lat2, double lng2)
{
    // Distance euclidienne simple (ou utilise la formule de Haversine si besoin)
    double dLat = lat - lat2;
    double dLng = lng - lng2;
    return std::sqrt(dLat * dLat + dLng * dLng);
}

// Algorithme :
//
//{
//} //----- Fin de distanceTo


string Sensor::getId()
// Algorithme :
//
{
    return id;
} //----- Fin de distanceTo


double Sensor::getLat()
// Algorithme :
//
{
    return lat;
} //----- Fin de distanceTo


double Sensor::getLng()
// Algorithme :
//
{
    return lng;
} //----- Fin de distanceTo


string Sensor::getUserId()
// Algorithme :
//
{
    return userId;
} //----- Fin de distanceTo


vector<Measurement> Sensor::getAllMeasurement()
{
    

    return measurements;
}


void Sensor::setId(string Id)
{
    id = Id;
}

void Sensor::setLat(double Lat)
{
    lat = Lat;
}

void Sensor::setLng(double Lng)
{
    lng = Lng;
}

void Sensor::setUserId(string userid)
{
    userId = userid;
}

vector<Sensor> Sensor::getSensorNeighbours(vector<Sensor> * sensors)
{
    vector<Sensor> nearby_sensors;   
    int i;
    int n = sensors->size();
    int distance = 0;
    int radius = 120;
    for ( auto& s : *sensors)
    {
        distance = distanceTo(s.getLat(), s.getLng());
        if (distance <= radius)
        {
            nearby_sensors.push_back(s); 
        }
    }
    return nearby_sensors;
    
} //----- Fin de getSensorNeighbours
// Algorithme :
//
//{
//} //----- Fin de getMeasurements

vector<Measurement> Sensor::getMeasurements(time_t period_start, time_t period_end)
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
}
// Algorithme :
//
//{
//} //----- Fin de getMeasurements

vector<Measurement> Sensor::getClosestMeasurements(time_t instant, int before_after)
{
    vector<Measurement> filtered;

    // Parcourt toutes les mesures
    for (Measurement m : measurements)
    {
        time_t ts = m.getTs();

        // Avant l'instant
        if (before_after < 0 && ts < instant)
        {
            filtered.push_back(m);
        }
        // Après l'instant
        else if (before_after > 0 && ts > instant)
        {
            filtered.push_back(m);
        }
    }

    return filtered;
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
Sensor::Sensor ( const Sensor & unSensor )
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