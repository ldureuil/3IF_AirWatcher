/*************************************************************************
Cleaner  -  Objet métier stockant les informations des Cleaners
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
#include <vector>
#include <ctime>

//------------------------------------------------------------------------
// Rôle de la classe <Cleaner>
// Objet métier Cleaner stockant l'id du cleaner, sa latitude, longitude
// et la période d'activité allant de start à stop
//------------------------------------------------------------------------

class Cleaner
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    vector<Sensor> getNeighbouringSensors( int radius, vector<Sensor>* sensors );
    // Mode d'emploi :
    //
    // Contrat :
    //

    // ---------------------------------------------------- Getters / Setters
    string getId( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    double getLat( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    double getLng( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    time_t getStart( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    time_t getEnd( );
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
    Cleaner( const Cleaner& unCleaner );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Cleaner( string p_id, double p_lat, double p_lng, time_t p_start, time_t p_end );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Cleaner( );
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
