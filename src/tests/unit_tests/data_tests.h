/*************************************************************************
data_tests  -  tests unitaires des méthodes de la couche Data
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//----- Interface de la classe <data_tests> (fichier data_tests.h) ------
#ifndef DATA_TESTS_H
#define DATA_TESTS_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <data_tests>
// Exécute les tests unitaires pour les méthodes de la couche Data
//------------------------------------------------------------------------

class data_tests
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    void runTests();
    // Mode d'emploi : Exécute les tests unitaires pour les méthodes de la couche Data
    //
    // Contrat :
    //

    //-------------------------------------------- Constructeurs - destructeur
    data_tests( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~data_tests( );
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



#endif //DATA_TESTS_H
