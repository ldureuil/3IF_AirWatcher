/*************************************************************************
UserDataAccess - Permet de charger et modifier les informations des particuliers
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//-- Interface de la classe <UserDataAccess> (fichier UserDataAccess.h) --
#ifndef USERDATAACCESS_H
#define USERDATAACCESS_H

//--------------------------------------------------- Interfaces utilisées
#include "../Data/ParticulierData.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
#include <vector>
#include <string>

//------------------------------------------------------------------------
// Rôle de la classe <UserDataAccess>
// Permet de charger et modifier les informations liées aux particuliers,
// à savoir leur nombre de points et leur statut (exclus ou non), à partir
// du fichier ParticulierData.csv
//------------------------------------------------------------------------

class UserDataAccess
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques

    bool initializeCSVFile( string filename );
    // Mode d'emploi : Permet de créer un fichier CSV avec les en-têtes userId, points et excluded.
    // Si le fichier existe déjà, il ne sera pas créé à nouveau.

    vector<ParticulierData> loadParticulierData( );
    // Mode d'emploi : Permet de créer pour chaaque utilisateur un objet ParticulierData
    // stockant son nombre de points et est-ce qu'il est exclus, à partir du fichier
    // ParticulierData.csv.

    int updateUserPoints( string userId );
    // Mode d'emploi : Permet de mettre à jour les points d'un utilisateur dans le fichier ParticulierData.csv.
    // Si le fichier n'xiste pas, il est créé avec l'userId donné en paramètre en lui donnant 10 points.
    // Si l'utilisateur existe déjà, ses points sont incrémentés de 10.
    // Si l'utilisateur n'est pas trouvé, il est ajouté avec 10 points.
    //
    // Contrat : paramètre userId doit être une chaîne de caractères valide représentant
    // l'identifiant de l'utilisateur et se trouvant dans le fichier users.csv.

    int addExcludedUser( string userId );
    // Mode d'emploi : Permet de changer le status d'un utilisateur dans le fichier ParticulierData.csv, il devient exclu.
    //
    // Contrat : paramètre userId doit être une chaîne de caractères valide représentant
    // l'identifiant de l'utilisateur et se trouvant dans le fichier users.csv.


    //------------------------------------------------- Surcharge d'opérateurs
    UserDataAccess& operator = ( const UserDataAccess& unUserDataAccess );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    UserDataAccess( const UserDataAccess& unUserDataAccess );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    UserDataAccess( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~UserDataAccess( );
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
