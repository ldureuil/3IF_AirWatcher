/*************************************************************************
UserDataAccess  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//-- Interface de la classe <UserDataAccess> (fichier UserDataAccess.h) --
#ifndef USERDATAACCESS_H
#define USERDATAACCESS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <list>

//------------------------------------------------------------------------
// Rôle de la classe <UserDataAccess>
// todo
//
//------------------------------------------------------------------------

class UserDataAccess
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    int loadUserPoints(string userId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    int updateUserPoints(string userId);
    // Mode d'emploi :
    //
    // Contrat :
    //

    list<string> loadExcludedUsers();
    // Mode d'emploi :
    //
    // Contrat :
    //

    int addExcludedUser(string userId);
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    UserDataAccess& operator = ( const UserDataAccess& unUserDataAccess );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    UserDataAccess ( const UserDataAccess& unUserDataAccess );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    UserDataAccess ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~UserDataAccess ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //USERDATAACCESS_H
