/*************************************************************************
Cleaner  -  Objet cleaner stockant l'id du cleaner, sa latitude, longitude
et la période d'activité allant de start à stop todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//------ Interface de la classe <Cleaner> (fichier Cleaner.h) ------------
#ifndef CLEANER_H
#define CLEANER_H

//--------------------------------------------------- Interfaces utilisées
#include "Sensor.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <list>
#include <ctime>

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
// todo
//
//------------------------------------------------------------------------

class Cleaner
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    list<Sensor> getNeighbouringSensors(int radius);
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    Cleaner& operator = ( const Cleaner& unCleaner );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    Cleaner ( const Cleaner& unCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Cleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Cleaner ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    string id;
    double lat;
    double lng;
    time_t start;
    time_t end;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //CLEANER_H
