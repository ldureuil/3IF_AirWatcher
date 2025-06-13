/*************************************************************************
Credentials  -  Objet métier stockant les credentials d'un utilisateur
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//----- Interface de la classe <Credentials> (fichier Credentials.h) -----
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

//--------------------------------------------------- Interfaces utilisées
#include "../Authentification/UserType.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Credentials>
// Objet métier Credentials stockant le login, le mot de passe et le type
// d'utilisateur de tous les utilisateurs de l'application.
//------------------------------------------------------------------------


class Credentials {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques


    // ---------------------------------------------------- Getters / Setters
    string getLogin ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getPassword ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    UserType getUserType ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //

    string getUserId ( ) const;
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    Credentials& operator = ( const Credentials& unCredentials );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    Credentials ( const Credentials& unCredentials );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Credentials ( string p_login = "", string p_password = "", UserType p_userType = UNDEFINED, string p_userId = "" );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Credentials ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    string login;
    string password;
    UserType userType;
    string userId;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //CREDENTIALS_H
