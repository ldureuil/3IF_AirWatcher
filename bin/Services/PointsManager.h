/*************************************************************************
PointsManager  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//--- Interface de la classe <PointsManager> (fichier PointsManager.h) ---
#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

//--------------------------------------------------- Interfaces utilisées
#include "../DataAccess/UserDataAccess.h"
#include "../Data/ParticulierData.h"
#include "../Data/Sensor.h"

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
    PointsManager( const PointsManager& unPointsManager );
    // Mode d'emploi :
    //
    // Contrat :
    //

    PointsManager( UserDataAccess p_uda, vector<ParticulierData>* p_particulierData, vector<Sensor>* p_sensors );
    // Mode d'emploi : Passe un pointeur vers un vecteur de capteurs pour
    // éviter une copie inutile
    // Contrat :
    //

    virtual ~PointsManager( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    UserDataAccess uda;
    vector<ParticulierData>* particulierData;
    vector<Sensor>* sensors;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //POINTSMANAGER_H
