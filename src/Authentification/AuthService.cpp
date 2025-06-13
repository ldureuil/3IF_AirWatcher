/*************************************************************************
AuthService  -  Service d'authentification des utilisateurs
                             -------------------
    début                : 15/05/2025
*************************************************************************/

//--- Réalisation de la classe <AuthService> (fichier AuthService.cpp) ---

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AuthService.h"
#include "../DataAccess/AuthDataAccess.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
Session AuthService::login( string credentialsFilePath, string login, string password )
// Algorithme : utilise la méthode findCredentials de AuthDataAccess
// pour vérifier les identifiants
{
    AuthDataAccess authDataAccess;
    Credentials credentials = authDataAccess.findCredentials(credentialsFilePath, login, password);

    if (credentials.getLogin().empty() || credentials.getPassword().empty()) {
        // Identifiants invalides
        return Session();
    } else {
        // Identifiants valides, créer une session
        currentSession = Session(credentials.getUserType(), credentials.getUserId());
        return currentSession;
    }
} //----- Fin de login

bool AuthService::checkRequiredRole( UserType role )
// Algorithme : Vérifie si le rôle de l'utilisateur dans la session correspond au rôle requis
{
    // Vérifie si le rôle de l'utilisateur dans la session correspond au rôle requis
    if (currentSession.getUserType() == role) {
        return true;
    } else {
        return false;
    }
} //----- Fin de checkRequiredRole

bool AuthService::setCurrentSession ( UserType userType, string userId )
// Algorithme : Définit la session courante
{
    currentSession = Session(userType, userId);
    return true;
} //----- Fin de setCurrentSession


//------------------------------------------------- Surcharge d'opérateurs
AuthService& AuthService::operator = ( const AuthService& unAuthService )
// Algorithme : Copie la session courante si this est différent de unAuthService
//
{
    if (this != &unAuthService)
    {
        this->currentSession = unAuthService.currentSession;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AuthService::AuthService ( const AuthService & unAuthService )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AuthService>" << endl;
#endif
} //----- Fin de AuthService (constructeur de copie)


AuthService::AuthService ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AuthService>" << endl;
#endif
} //----- Fin de AuthService


AuthService::~AuthService ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AuthService>" << endl;
#endif
} //----- Fin de ~AuthService


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
