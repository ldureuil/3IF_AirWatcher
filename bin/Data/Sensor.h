/*************************************************************************
Sensor  -  Objet métier stockant les informations d'un capteur
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//------ Interface de la classe <Sensor> (fichier Sensor.h) ------------
#ifndef SENSOR_H
#define SENSOR_H

//--------------------------------------------------- Interfaces utilisées
#include "Measurement.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

#include <vector>
#include <ctime>

//------------------------------------------------------------------------
// Rôle de la classe <Sensor>
// Objet métier Sensor stockant l'id du capteur, sa latitude, longitude,
// une liste des mesures effectuées et l'id du particulier qui le possède
// si c'est un capteur privé
//------------------------------------------------------------------------

class Sensor {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    double distanceTo( double lat, double lng );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Sensor> getSensorNeighbours( vector<Sensor>* sensors, int radius = 120 );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> getMeasurements( time_t period_start, time_t period_end );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> getClosestMeasurements( time_t instant, int before_after );
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

    string getUserId( );
    // Mode d'emploi :
    // return un string vide si le capteur n'est pas privé
    // Contrat :
    //

    vector<Measurement> getAllMeasurements( );
    // Mode d'emploi :
    // retourne le vecteur des mesures du capteur
    // Contrat :
    //
    
    bool setId( string p_id );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    bool setLat( double p_lat );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    bool setLng( double p_lng );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setMeasurements( vector<Measurement> p_measurements );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setUserId( string p_userId );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    Sensor& operator = ( const Sensor& unSensor );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    Sensor( const Sensor& unSensor );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Sensor( );
    // Mode d'emploi :
    // constructeur non paramétré nécessaire lors du chargement de la base de
    // données car les données ne sont pas stockées dans un seul fichier
    // Contrat :
    //

    Sensor( string p_id, double p_lat, double p_lng, vector<Measurement> p_measurements, string p_userId );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor( );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------------------------ PRIVE
private:
    string id;
    double lat;
    double lng;
    vector<Measurement> measurements;
    string userId;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //SENSOR_H
