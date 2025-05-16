/*************************************************************************
Credentials  -  todo
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
// todo
//
//------------------------------------------------------------------------


class Credentials {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques

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

    Credentials ( );
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

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //CREDENTIALS_H
