/*************************************************************************
dataLoader_tests  -  tests unitaires des méthodes de la couche DataLoader
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Interface de la classe <dataLoader_tests> (fichier dataLoader_tests.h) -
#ifndef DATALOADER_TESTS_H
#define DATALOADER_TESTS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <dataLoader_tests>
// Exécute les tests unitaires pour les méthodes de la couche DataLoader
//------------------------------------------------------------------------

class dataLoader_tests {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    void runTests();
    // Mode d'emploi : Exécute les tests unitaires pour les méthodes de la couche DataLoader
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    dataLoader_tests( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~dataLoader_tests( );
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



#endif //DATALOADER_TESTS_H
