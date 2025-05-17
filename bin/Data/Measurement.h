/*************************************************************************
Measurement  - Objet métier stockant les informations d'une mesure
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//----- Interface de la classe <Measurement> (fichier Measurement.h) -----
#ifndef MEASUREMENT_H
#define MEASUREMENT_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <ctime>

//------------------------------------------------------------------------
// Rôle de la classe <Measurement>
// Objet métier Measurement stockant le timestamp de la mesure, l'id de son
// attribut, l'unité de son attribut, la description de son attribut et sa
// valeur
//------------------------------------------------------------------------

class Measurement
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    bool isWithin( time_t period_start, time_t period_end );
    // Mode d'emploi :
    //
    // Contrat :
    //

    // ---------------------------------------------------- Getters / Setters
    time_t getTs( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getAttr_id( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    string getAttr_unit( );
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    string getAttr_desc( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    double getValue( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setTs( time_t p_ts );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setAttr_id( string p_attr_id );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setAttr_unit( string p_attr_unit );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setAttr_desc( string p_attr_desc );
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool setValue( double p_value );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    Measurement& operator = ( const Measurement& unMeasurement );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    Measurement( const Measurement& unMeasurement );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Measurement( time_t p_ts, string p_attr_id, string p_attr_unit, string p_attr_desc, double p_value );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Measurement( );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------------------------ PRIVE
private:
    time_t ts;
    string attr_id;
    string attr_unit;
    string attr_desc;
    double value;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //MEASUREMENT_H
