/*************************************************************************
PointsManager  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//--- Interface de la classe <PointsManager> (fichier PointsManager.h) ---
#ifndef POINTSMANAGER_H
#define POINTSMANAGER_H

//--------------------------------------------------- Interfaces utilisées

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
    bool award(vector<string> sensorsUsed);
    // Mode d'emploi :
    //
    // Contrat :
    //

    int getPoints(string userId);
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs

    //-------------------------------------------- Constructeurs - destructeur
    PointsManager ( UserDataAccess Uda , DataLoader dataloader);
    // Mode d'emploi :
    //
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
     
    UserDataAccess uda;
    DataLoader dl;
    //----------------------------------------------------- Attributs protégés
};



#endif //POINTSMANAGER_H
