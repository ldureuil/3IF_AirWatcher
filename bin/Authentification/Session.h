/*************************************************************************
Session  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//------ Interface de la classe <Session> (fichier Session.h) ------------
#ifndef SESSION_H
#define SESSION_H

//--------------------------------------------------- Interfaces utilisées
#include "UserType.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Session>
// todo
//
//------------------------------------------------------------------------

class Session {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    UserType getUserType ( );
    string getUserID ( );

    //------------------------------------------------- Surcharge d'opérateurs
    Session& operator = ( const Session& unSession );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    Session ( const Session& unSession );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Session ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Session ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    string userId;
    UserType userType;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //SESSION_H
