/*************************************************************************
Statistics  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//------ Interface de la classe <Statistics> (fichier Statistics.h) ------
#ifndef STATISTICS_H
#define STATISTICS_H

//--------------------------------------------------- Interfaces utilisées
#include "../Data/Sensor.h"
#include "../Data/Cleaner.h"
#include "../Data/Measurement.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <vector>
#include <ctime>

//------------------------------------------------------------------------
// Rôle de la classe <Statistics>
// todo
//
//------------------------------------------------------------------------

class Statistics {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    int analyzeSensor( string sensorID );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<int> analyzeCleaner( string cleanerID, int radius = 100 );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> computeZone( double lat, double lng, time_t period_start, time_t period_end = 0, int radius = 0);
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Sensor> compareSensors( string sensorId, time_t period_start, time_t period_end );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> extrapolateAQI( double lat, double lng, time_t period_start, time_t period_end );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Sensor getSensorByID( string id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Cleaner getCleanerByID( string id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------- Surcharge d'opérateurs
    Statistics& operator = ( const Statistics& unStatistics );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    Statistics( const Statistics& unStatistics );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Statistics( vector<Sensor>* p_sensors, vector<Cleaner>* p_cleaners );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Statistics( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    vector<Sensor>* sensors;
    vector<Cleaner>* cleaners;
};



#endif //STATISTICS_H