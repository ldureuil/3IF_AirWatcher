/*************************************************************************
ParticulierData  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Interface de la classe <ParticulierData> (fichier ParticulierData.h) -
#ifndef PARTICULIERDATA_H
#define PARTICULIERDATA_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ParticulierData>
// todo
//
//------------------------------------------------------------------------

class ParticulierData
{
    //----------------------------------------------------------------- PUBLIC
public:
    //----------------------------------------------------- Méthodes publiques

    //------------------------------------------------- Surcharge d'opérateurs
    ParticulierData& operator = ( const ParticulierData& unParticulierData );
    // Mode d'emploi :
    //
    // Contrat :
    //


    //-------------------------------------------- Constructeurs - destructeur
    ParticulierData( const ParticulierData& unParticulierData );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    ParticulierData( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~ParticulierData( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    //------------------------------------------------------------------ PRIVE
private:
    string id;
    int points;
    bool isExcluded;

protected:
    //----------------------------------------------------- Méthodes protégées

    //----------------------------------------------------- Attributs protégés
};



#endif //PARTICULIERDATA_H
