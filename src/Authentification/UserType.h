/*************************************************************************
UserType  -  Énumération des 5 types d'utilisateurs de l'application
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//------ Interface du module <UserType> (fichier UserType.h) ------------
#ifndef USERTYPE_H
#define USERTYPE_H

//------------------------------------------------------------------------
// Rôle du module <UserType>
// Énumération des 5 types d'utilisateurs de l'application, permettant de 
// déterminer les fonctionnalités qui leur sont autorisées.
//------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////  INCLUDE
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
enum UserType
{
    ADMIN = 0,
    USER = 1,
    PARTICULIER = 2,
    FOURNISSEUR = 3,
    UNDEFINED = 4
};

#endif //USERTYPE_H
