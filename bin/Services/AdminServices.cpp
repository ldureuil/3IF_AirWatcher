/*************************************************************************
AdminServices  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <AdminServices> (fichier AdminServices.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AdminServices.h"
#include "../DataAccess/UserDataAccess.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int AdminServices::excludeSensor(string sensorId)
{

    uda.addExcludedUser(sensorId);

}
// Algorithme :
//
//{
//} //----- Fin de excludeSensor


//------------------------------------------------- Surcharge d'opérateurs
AdminServices& AdminServices::operator=(const AdminServices& unAdminServices)
{
    if (this != &unAdminServices) 
    {
        uda = unAdminServices.uda;
        
    }

    return *this; 
}

//-------------------------------------------- Constructeurs - destructeur
AdminServices::AdminServices ( const AdminServices & unAdminServices )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AdminServices>" << endl;
#endif

    uda = unAdminServices.uda;
} //----- Fin de AdminServices (constructeur de copie)


AdminServices::AdminServices ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AdminServices>" << endl;
#endif
} //----- Fin de AdminServices


AdminServices::~AdminServices ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AdminServices>" << endl;
#endif
} //----- Fin de ~AdminServices


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
