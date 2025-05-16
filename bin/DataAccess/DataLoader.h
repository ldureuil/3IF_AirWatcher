/*************************************************************************
DataLoader  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//------ Interface de la classe <DataLoader> (fichier DataLoader.h) ------
#ifndef DATALOADER_H
#define DATALOADER_H

//--------------------------------------------------- Interfaces utilisées
#include "../Data/Sensor.h"
#include "../Data/Cleaner.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <list>

//------------------------------------------------------------------------
// Rôle de la classe <DataLoader>
// todo
//
//------------------------------------------------------------------------

class DataLoader {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    void loadData();
    // Mode d'emploi :
    //
    // Contrat :
    //

    Sensor* getSensor(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<Sensor*> getSensors();
    // Mode d'emploi :
    //
    // Contrat :
    //

    Cleaner* getCleaner(string cleanerId);
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
    DataLoader ( const DataLoader& unDataLoader );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    DataLoader ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~DataLoader ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    list<Sensor*> sensors;
    list<Cleaner*> cleaners;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //DATALOADER_H
