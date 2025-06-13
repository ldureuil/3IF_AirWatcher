/*************************************************************************
DataLoader  -  Charge les données de la base de données
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//------ Interface de la classe <DataLoader> (fichier DataLoader.h) ------
#ifndef DATALOADER_H
#define DATALOADER_H

//--------------------------------------------------- Interfaces utilisées
#include "../Data/Sensor.h"
#include "../Data/Cleaner.h"
#include "../Authentification/UserType.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <vector>

//------------------------------------------------------------------------
// Rôle de la classe <DataLoader>
// Charge les données de la base de données dans des vecteurs d'objets
// Sensor et Cleaner attributs de la classe pour utiliser le pointeur
// vers cette liste dans les services de l'application
//------------------------------------------------------------------------

class DataLoader {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    vector<Sensor>* loadSensor( string databasePath, UserType userType );
    // Mode d'emploi :
    //
    // Contrat :
    //

    vector<Cleaner>* loadCleaner( string databasePath, UserType userType );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    DataLoader& operator = ( const DataLoader& unDataLoader );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    DataLoader( const DataLoader& unDataLoader );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    DataLoader( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~DataLoader( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    vector<Sensor> sensors;
    vector<Cleaner> cleaners;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //DATALOADER_H
