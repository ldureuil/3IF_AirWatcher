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
    // Mode d'emploi : exécute les tests unitaires pour la couche DataLoader
    //
    // Contrat :
    //

    void testLoadSensorWithData();
    // Mode d'emploi : teste la méthode loadSensor avec la base de données entière
    //
    // Contrat :
    //

    void testLoadSensorWithEmptyData();
    // Mode d'emploi : teste la méthode loadSensor avec une base de données vide
    //
    // Contrat :
    //

    void testLoadCleanerWithData();
    // Mode d'emploi : teste la méthode loadCleaner avec la base de données entière
    //
    // Contrat :
    //

    void testLoadCleanerWithEmptyData();
    // Mode d'emploi : teste la méthode loadCleaner avec une base de données vide
    //
    // Contrat :
    //

    void testFindCredentialsWithEmptyFile();
    // Mode d'emploi : teste la méthode findCredentials avec un fichier CSV vide
    //
    // Contrat :
    //

    void testFindCredentialsWithData();
    // Mode d'emploi : teste la méthode findCredentials avec des données valides
    //
    // Contrat :
    //

    void testFindCredentialsWrongLogin();
    // Mode d'emploi : teste la méthode findCredentials avec un login inexistant
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
