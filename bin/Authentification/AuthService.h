/*************************************************************************
AuthService  -  todo
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//----- Interface de la classe <AuthService> (fichier AuthService.h) -----
#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

//--------------------------------------------------- Interfaces utilisées
#include "UserType.h"
#include "Session.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AuthService>
// todo
//
//------------------------------------------------------------------------

class AuthService {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    Session login(string login, string password);
    // Mode d'emploi :
    //
    // Contrat :
    //

    bool checkRequiredRole(Session session, UserType role);
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    AuthService& operator = ( const AuthService& unAuthService );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    AuthService ( const AuthService& unAuthService );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    AuthService ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AuthService ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE


protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //AUTHSERVICE_H
