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
#include "../Data/Measurement.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <list>
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
    int analyzeSensor(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<int> analyzeCleaner(string cleanerId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<int> analyzeStatistics(string StatisticsId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<Measurement> computeZone(double lat, double lng, time_t period_start, time_t period_end, int radius);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<Sensor> compareSensors(string sensorId, time_t period_start, time_t period_end);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<Measurement> extrapolateAQI(double lat, double lng, time_t period_start, time_t period_end);
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
    Statistics ( const Statistics& unStatistics );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Statistics ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Statistics ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //STATISTICS_H
