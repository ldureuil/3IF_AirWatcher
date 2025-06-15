/*************************************************************************
AdminServices  -  Services critiques associés au rôle administrateur
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//--- Interface de la classe <AdminServices> (fichier AdminServices.h) ---
#ifndef ADMINSERVICES_H
#define ADMINSERVICES_H

//--------------------------------------------------- Interfaces utilisées
#include "../DataAccess/UserDataAccess.h"
#include "../Data/Sensor.h"
#include "../Services/Statistics.h"
#include "../Authentification/AuthService.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AdminServices>
// Services associés au rôle administrateur, à savoir l'exclusion d'un capteur
// suspect et l'évaluation des temps d'exécution des différentes requêtes de
// l'application.
//------------------------------------------------------------------------

class AdminServices {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    bool excludeSensor( string sensorId, string pointsFile = "../data/ParticulierData.csv" );
    // Mode d'emploi : Permet d'exclure le particulier correspondant au sensorId
    // passé en paramètre, si le capteur appartient bien à un particulier.
    // Contrat :
    //

    vector<double> evaluate(Statistics& stats);
    // Mode d'emploi : Permet d'obtenir le temps d'exécution de chaque requête
    // classique de l'application
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

    AdminServices( UserDataAccess p_uda, vector<Sensor>* p_sensors, AuthService* p_authService );
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
    AuthService* authService;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //ADMINSERVICES_H
