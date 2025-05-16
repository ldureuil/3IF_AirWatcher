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
#include <list>

//------------------------------------------------------------------------
// Rôle de la classe <PointsManager>
// todo
//
//------------------------------------------------------------------------

class PointsManager {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    bool award(list<string> sensorsUsed);
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

    PointsManager ( );
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

    //----------------------------------------------------- Attributs protégés
};



#endif //POINTSMANAGER_H
