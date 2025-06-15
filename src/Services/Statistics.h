/*************************************************************************
Statistics  -  Services métiers de base de l'application
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
#include "PointsManager.h"
#include "../Authentification/AuthService.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <vector>
#include <ctime>

//------------------------------------------------------------------------
// Rôle de la classe <Statistics>
// Statistics permet d'effectuer toutes les requêtes de base de l'application
// (moyennes de la qualité de l'air, analyse et comparaison de capteurs, analyse)
// de cleaners).
//------------------------------------------------------------------------

class Statistics {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    int analyzeSensor( string sensorID );
    // Mode d'emploi : Permet d'analyser la fiabilité d'un capteur en le
    // comparant avec ses voisins sur sa période de mise en service. Renvoie
    // -1 en cas d'erreur, 0 s'il est suspect et 1 s'il semble fiable.
    // Contrat :
    //

    vector<Measurement> analyzeCleaner( string cleanerID, int radius = 100 );
    // Mode d'emploi : Retourne les pourcentages d'amélioration de l'air dans la
    // zone autour d'un cleaner avant et après son action, pour chacun des 
    // indicateurs de l'AQI.
    // Contrat : Le rayon doit être en mètres.
    //

    vector<Measurement> computeZone( double lat, double lng, time_t period_start, time_t period_end, int radius = 0, int radiusExtrapolation = 0, string pointsFile = "../data/ParticulierData.csv");
    // Mode d'emploi : Renvoie les moyennes des mesures enregistrées par les capteurs
    // présents dans la zone pour la période considérée. Si le rayon est à 0, extrapole
    // les mesures pour chaque indicateur.
    // Contrat : Les rayons doivent être en mètres.
    //

    vector<Sensor> compareSensors( string sensorId, time_t period_start, time_t period_end );
    // Mode d'emploi : Renvoie par ordre décroissants les 10 capteurs les plus
    // similaires au capteur étudié, sur la période considérée.
    // Contrat :
    //

    vector<Measurement> extrapolateAQI( double lat, double lng, time_t period_start, time_t period_end, int radiusExtrapolation );
    // Mode d'emploi : Renvoie une extrapolation de la qualité de l'air au point
    // considéré pour chaque indicateur, à partir des capteurs les plus proches.
    // La fonction renverra les indicateurs d'AQI pour chaque jour de la période étudiée.
    // Contrat : Le rayon doit être en mètres.
    //

    Sensor *getSensorByID( string id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Cleaner *getCleanerByID( string id );
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

    Statistics( vector<Sensor>* p_sensors, vector<Cleaner>* p_cleaners, PointsManager*  p_pointsManager, AuthService *p_authService );
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
    PointsManager* pointsManager;
    AuthService* authService;
};



#endif //STATISTICS_H