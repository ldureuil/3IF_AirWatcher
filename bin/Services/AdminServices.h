/*************************************************************************
AdminServices  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//--- Interface de la classe <AdminServices> (fichier AdminServices.h) ---
#ifndef ADMINSERVICES_H
#define ADMINSERVICES_H

//--------------------------------------------------- Interfaces utilisées
#include "../DataAccess/UserDataAccess.h"
#include "../DataAccess/Sensor.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AdminServices>
// todo
//
//------------------------------------------------------------------------

class AdminServices {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    bool excludeSensor( string sensorId );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    AdminServices& operator = ( const AdminServices& unAdminServices );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    AdminServices( const AdminServices& unAdminServices );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    AdminServices( UserDataAccess p_uda, vector<Sensor>* p_sensors );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AdminServices( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    UserDataAccess uda;
    vector<Sensor>* sensors;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //ADMINSERVICES_H
