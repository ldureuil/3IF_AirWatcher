/*************************************************************************
AuthDataAccess  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//-- Interface de la classe <AuthDataAccess> (fichier AuthDataAccess.h) --
#ifndef AUTHDATAACCESS_H
#define AUTHDATAACCESS_H

//--------------------------------------------------- Interfaces utilisées
#include "../Data/Credentials.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <list>

//------------------------------------------------------------------------
// Rôle de la classe <AuthDataAccess>
// todo
//
//------------------------------------------------------------------------

class AuthDataAccess
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    list<Credentials> loadCredentials();
    // Mode d'emploi :
    //
    // Contrat :
    //

    Credentials findCredentials();
    // Mode d'emploi :
    //
    // Contrat :
    //



    //------------------------------------------------- Surcharge d'opérateurs
    AuthDataAccess& operator = ( const AuthDataAccess& unAuthDataAccess );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    AuthDataAccess ( const AuthDataAccess& unAuthDataAccess );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    AuthDataAccess ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AuthDataAccess ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //AUTHDATAACCESS_H
