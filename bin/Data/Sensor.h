/*************************************************************************
Sensor  -  todo
                             -------------------
    début                : 16/05/2025
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
// todo
//
//------------------------------------------------------------------------


class Sensor {
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    double distanceTo(double lat, double lng);
    // Mode d'emploi :
    //
    // Contrat :
    //


    string getId();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    double getLat();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    double getLng();
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getUserId();
    // Mode d'emploi :
    //
    // Contrat :
    //

    
    void setId(string);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void setLat(double);
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    void setLng(double);
    // Mode d'emploi :
    //
    // Contrat :
    //

    

    void setUserId(string userid);
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Sensor> getSensorNeighbours(vector<Sensor> sensors);
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> getMeasurements(time_t period_start, time_t period_end);
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Measurement> getClosestMeasurements(time_t instant, int before_after);
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
    Sensor ( const Sensor& unSensor );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Sensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Sensor ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    string id;
    double lat;
    double lng;
    vector<Measurement *> measurements;
    string userId;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //SENSOR_H
