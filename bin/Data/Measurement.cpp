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




void Measurement::setTs(time_t time)
{
    ts = time;
    
}
// Algorithme :
//
//{
//} //----- Fin de isWithin

void Measurement::setAttr_desc(string desc)
{
    attr_desc = desc;
}   
// Algorithme :
//
//{
//} //----- Fin de isWithin

void Measurement::setAttr_unit(string unit)
{
    attr_unit = unit;
}
   
// Algorithme :
//
//{
//} //----- Fin de isWithin

void Measurement::setValue(double val)
{
    value = val;
}
  
// Algorithme :
//
//{
//} //----- Fin de isWithin

time_t Measurement::getTs()
{
    return ts;
}
   
// Algorithme :
//
//{
//} //----- Fin de isWithin
   
string Measurement::getAttr_desc()
{
    return attr_desc;
}
    
// Algorithme :
//
//{
//} //----- Fin de isWithin
   
string Measurement::getAttr_unit()
{
    return attr_unit;
}
    
// Algorithme :
//
//{
//} //----- Fin de isWithin

double Measurement::getValue()
{
    return value;
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

    Measurement mesurement  = Measurement(unMeasurement);
    return mesurement;

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
    attr_desc = unMeasurement.attr_desc; 
    attr_unit = unMeasurement.attr_unit;
    value = unMeasurement.value;
} //----- Fin de Measurement (constructeur de copie)


Measurement::Measurement ( time_t time, string unit, string desc, double val )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Measurement>" << endl;
#endif

    ts = time;
    attr_desc = unit ;
    attr_unit = desc;
    value = val;
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
