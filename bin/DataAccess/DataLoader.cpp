/*************************************************************************
DataLoader  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---- Réalisation de la classe <DataLoader> (fichier DataLoader.cpp) ----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataLoader.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
void DataLoader::loadData()
{
}
// Algorithme :
//
//{
//} //----- Fin de loadData

Sensor* DataLoader::getSensor(string sensorId)
{
}
// Algorithme :
//
//{
//} //----- Fin de getSensor

list<Sensor*> DataLoader::getSensors()
{
}
// Algorithme :
//
//{
//} //----- Fin de getSensors

Cleaner* DataLoader::getCleaner(string cleanerId)
{
}
// Algorithme :
//
//{
//} //----- Fin de getCleaner


//------------------------------------------------- Surcharge d'opérateurs
DataLoader& DataLoader::operator = ( const DataLoader& unDataLoader )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
DataLoader::DataLoader ( const DataLoader & unDataLoader )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <DataLoader>" << endl;
#endif
} //----- Fin de DataLoader (constructeur de copie)


DataLoader::DataLoader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <DataLoader>" << endl;
#endif
} //----- Fin de DataLoader


DataLoader::~DataLoader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DataLoader>" << endl;
#endif
} //----- Fin de ~DataLoader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
