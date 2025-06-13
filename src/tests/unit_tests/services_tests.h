/*************************************************************************
services_tests  -  tests unitaires des méthodes de la couche services
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//-- Interface de la classe <services_tests> (fichier services_tests.h) --
#ifndef SERVICES_TESTS_H
#define SERVICES_TESTS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <services_tests>
// Exécute les tests unitaires pour les méthodes de la couche Services
//------------------------------------------------------------------------

class Services_Tests
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    void runTests();
    // Mode d'emploi : Exécute les tests unitaires pour les méthodes de la couche Services
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    services_tests( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~services_tests( );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------------------------ PRIVE
private:

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};


#endif //SERVICES_TESTS_H
