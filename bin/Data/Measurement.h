/*************************************************************************
Measurement  -  todo
                             -------------------
    début                : 16/05/2025
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
// todo
//
//------------------------------------------------------------------------


class Measurement {
    //----------------------------------------------------------------- PUBLIC

public:
    //----------------------------------------------------- Méthodes publiques
    bool isWithin(time_t period_start, time_t period_end);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setTs(time_t time);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setAttr_desc(string desc);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setAttr_unit(string unit);
    // Mode d'emploi :
    //
    // Contrat :
    //

    void setValue(double val);
    // Mode d'emploi :
    //
    // Contrat :
    //


    time_t getTs();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    string getAttr_desc();
    // Mode d'emploi :
    //
    // Contrat :
    //
    
    string getAttr_unit();
    // Mode d'emploi :
    //
    // Contrat :
    //

    double getValue();
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
    Measurement ( const Measurement& unMeasurement );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Measurement (time_t time, string unit, string desc, double val );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Measurement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    time_t ts;
    string attr_unit;
    string attr_desc;
    double value;

    


protected:
    //----------------------------------------------------- Méthodes protégées

    
    


    //----------------------------------------------------- Attributs protégés
};



#endif //MEASUREMENT_H
