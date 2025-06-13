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


    // ---------------------------------------------------- Getters / Setters
    string getId() const;
    // Mode d'emploi :
    // Renvoie l'identifiant du particulier
    // Contrat :
    //

    int getPoints() const;
    // Mode d'emploi :
    // Renvoie le nombre de points du particulier
    // Contrat :
    //

    bool getIsExcluded() const;
    // Mode d'emploi :
    // Renvoie si le particulier est exclu
    // Contrat :
    //

    bool setId(string p_id);
    // Mode d'emploi :
    // Modifie l'identifiant du particulier
    // Contrat :
    //

    bool setPoints(int p_points);
    // Mode d'emploi :
    // Modifie le nombre de points du particulier
    // Contrat :
    //

    bool setIsExcluded(bool p_isExcluded);
    // Mode d'emploi :
    // Modifie si le particulier est exclu
    // Contrat :
    //


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

    ParticulierData( string p_id, int p_points, bool p_isExcluded );
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
