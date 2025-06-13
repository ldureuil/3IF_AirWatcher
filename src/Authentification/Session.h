/*************************************************************************
Session  -  Classe de gestion des sessions utilisateur
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
// Cette classe gère les sessions utilisateur, en stockant le type d'utilisateur
//------------------------------------------------------------------------

class Session {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    UserType getUserType ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getUserId ( ) const;

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

    Session ( UserType p_userType, string p_userId = "" );
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
    UserType userType;
    string userId;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //SESSION_H
