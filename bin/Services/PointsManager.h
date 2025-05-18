/*************************************************************************
PointsManager  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//--- Interface de la classe <PointsManager> (fichier PointsManager.h) ---
#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include "Sensor.h"
#include "UserDataAccess.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <vector>

//------------------------------------------------------------------------
// Rôle de la classe <PointsManager>
// todo
//
//------------------------------------------------------------------------

class PointsManager {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    bool award(const vector<string>& sensorsUsed);
    // Mode d'emploi : on attribue des points à un ou plusieurs utilisateurs 
    // en fonction des capteurs utilisés.
    // Contrat : 
    //

    int getPoints(string userId);
    // Mode d'emploi : permet de récupérer le nombre de points d'un utilisateur.
    // 
    // Contrat : L'utilisateur doit exister dans le fichier ParticulierData.csv

    void setSensors(vector<Sensor>* sensors);
    // Mode d'emploi :
    // Permet de définir le vecteur de capteurs à utiliser pour la gestion des points.
    // Contrat :

    vector<Sensor>* getSensors();
    // Mode d'emploi :
    // Permet de récupérer le vecteur de capteurs.

    //------------------------------------------------- Surcharge d'opérateurs
    PointsManager& operator = ( const PointsManager& unPointsManager );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    PointsManager ( const PointsManager& unPointsManager );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    PointsManager (vector<Sensor>* sensors = nullptr);
    // Mode d'emploi (constructeur par défaut) : il prend en paramètre un vecteur de capteurs initialisé gràce à la méthode loadSensor 
    // de la classe DataLoader.
    // Contrat :
    //

    virtual ~PointsManager ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
    vector<Sensor>* sensors;
};



#endif //POINTSMANAGER_H
