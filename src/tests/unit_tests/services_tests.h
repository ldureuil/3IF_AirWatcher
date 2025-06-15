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

class services_tests
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    int runTests();
    // Mode d'emploi : Exécute les tests unitaires pour les méthodes de la couche Services
    //
    // Contrat :
    //

    bool testAnalyzeSensorInexistant();
    bool testAnalyzeSensorSansMesure();
    bool testAnalyzeSensorAnormal();
    bool testAnalyzeSensorNormal();

    bool testComputeZoneAucunCapteur();
    bool testComputeZoneSansMesures();
    bool testComputeZoneEstimationPonctuelle();
    bool testComputeZoneAvecCapteurs();

    bool testAnalyzeCleanerInconnu();
    bool testAnalyzeCleanerSansCapteurs();
    bool testAnalyzeCleanerValide();

    bool testCompareSensorsInexistant();
    bool testCompareSensorsAucunCapteur();
    bool testCompareSensorsValide();

    bool testExtrapolateAQISansMesures();
    bool testExtrapolateAQIValide();

    bool testAwardListeVide();
    bool testAwardCapteurUnique();
    bool testAwardDeuxCapteursUtilisateurs();
    bool testAwardDeuxCapteursMemUtilisateur();
    bool testAwardCapteurInconnu();
    bool testAwardCapteurExclu();
    bool testAwardCapteursValidesEtExclus();
    bool testAwardCapteurSansUtilisateur();
    bool testAwardCapteursValidesEtSansUtilisateur();

    bool testGetPointsUtilisateurInexistant();
    bool testGetPointsUtilisateurExistant();

    bool testExcludeSensorInexistant();
    bool testExcludeSensorDejaExclu();
    bool testExcludeSensorValide();

    bool testLoginCombiValide();
    bool testLoginCombiInvalide();
    bool testCheckRequiredRolePrivilegeSuperieur();
    bool testCheckRequiredRolePrivilegeInferieur();

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
