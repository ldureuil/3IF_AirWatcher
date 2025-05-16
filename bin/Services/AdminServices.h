/*************************************************************************
AdminServices  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//--- Interface de la classe <AdminServices> (fichier AdminServices.h) ---
#ifndef ADMINSERVICES_H
#define ADMINSERVICES_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <AdminServices>
// todo
//
//------------------------------------------------------------------------

class AdminServices {
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques
    int excludeSensor(string sensorId);
    // Mode d'emploi :
    //
    // Contrat :
    //


    //------------------------------------------------- Surcharge d'opérateurs
    AdminServices& operator = ( const AdminServices& unAdminServices );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    AdminServices ( const AdminServices& unAdminServices );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    AdminServices ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~AdminServices ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //ADMINSERVICES_H
