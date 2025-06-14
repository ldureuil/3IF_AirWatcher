/*************************************************************************
AuthService  -  Service d'authentification des utilisateurs
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//----- Interface de la classe <AuthService> (fichier AuthService.h) -----
#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

//--------------------------------------------------- Interfaces utilisées
#include "UserType.h"
#include "Session.h"
#include "../Data/Credentials.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AuthService>
// Cette classe gère l'authentification des utilisateurs. Elle permet aux
// utilisateurs de se connecter avec un identifiant et un mot de passe, et
// de vérifier s'ils ont les rôles requis pour effectuer certaines actions
// dans l'application.
//------------------------------------------------------------------------

class AuthService {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    Session login( string databasePath, string login, string password );
    // Mode d'emploi : Authentifie un utilisateur en vérifiant ses identifiants

    virtual bool checkRequiredRole( UserType role );
    // Mode d'emploi : Vérifie si le rôle de l'utilisateur dans la session correspond au rôle requis

    bool setCurrentSession ( UserType userType, string userId = "" );
    // Mode d'emploi : Définit la session courante


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
private:
    Session currentSession;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //AUTHSERVICE_H
