/*************************************************************************
AuthDataAccess  -  Lit les credentials dans la base de données pour
trouver un utilisateur
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
// Lit les credentials de la base de données pour retourner un objet Credentials
// permettant de vérifier les identifiants d'un utilisateur.
//------------------------------------------------------------------------

class AuthDataAccess
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    Credentials findCredentials( string databasePath, string p_login, string p_password );
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
