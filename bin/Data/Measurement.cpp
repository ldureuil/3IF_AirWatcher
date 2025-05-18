/*************************************************************************
Measurement  -  Objet métier stockant les informations d'une mesure
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
bool Measurement::isWithin( time_t period_start, time_t period_end )
// Algorithme :
//
{
    return ts >= period_start && ts <= period_end;
} //----- Fin de isWithin


// ---------------------------------------------------- Getters / Setters
time_t Measurement::getTs()
// Algorithme :
//
{
    return ts;
} //----- Fin de getTs

string Measurement::getAttr_id()
// Algorithme :
//
{
    return attr_id;
} //----- Fin de getAttr_id

string Measurement::getAttr_unit()
// Algorithme :
//
{
    return attr_unit;
} //----- Fin de getAttr_unit

   
string Measurement::getAttr_desc()
// Algorithme :
//
{
    return attr_desc;
} //----- Fin de getAttr_desc

double Measurement::getValue()
// Algorithme :
//
{
    return value;
} //----- Fin de getValue


bool Measurement::setTs(time_t p_ts)
// Algorithme :
//
{
    ts = p_ts;
    return true;
} //----- Fin de setTs

bool Measurement::setAttr_id(string p_attr_id)
// Algorithme :
//
{
    attr_id = p_attr_id;
    return true;
} //----- Fin de setAttr_id

bool Measurement::setAttr_unit(string p_attr_unit)
// Algorithme :
//
{
    attr_unit = p_attr_unit;
    return true;
} //----- Fin de setAttr_unit


bool Measurement::setAttr_desc(string p_attr_desc)
// Algorithme :
//
{
    attr_desc = p_attr_desc;
    return true;
} //----- Fin de setAttr_desc

bool Measurement::setValue(double p_value)
// Algorithme :
//
{
    value = p_value;
    return true;
} //----- Fin de setValue


//------------------------------------------------- Surcharge d'opérateurs
Measurement& Measurement::operator = ( const Measurement& unMeasurement )
// Algorithme :
//
{
    if (this != &unMeasurement)
    {
        ts = unMeasurement.ts;
        attr_id = unMeasurement.attr_id;
        attr_desc = unMeasurement.attr_desc;
        attr_unit = unMeasurement.attr_unit;
        value = unMeasurement.value;
    }

    return *this;

} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Measurement::Measurement ( const Measurement & unMeasurement )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Measurement>" << endl;
#endif
    ts = unMeasurement.ts;
    attr_id = unMeasurement.attr_id;
    attr_desc = unMeasurement.attr_desc;
    attr_unit = unMeasurement.attr_unit;
    value = unMeasurement.value;
} //----- Fin de Measurement (constructeur de copie)

Measurement::Measurement ( time_t p_ts, string p_attr_id, string p_attr_unit, string p_attr_desc, double p_value )
// Algorithme :
//
: ts(p_ts), attr_id(p_attr_id), attr_unit(p_attr_unit), attr_desc(p_attr_desc), value(p_value)
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
