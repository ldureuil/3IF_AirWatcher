/*************************************************************************
AuthDataAccess  -  Lit les credentials dans la base de données pour
trouver un utilisateur
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <AuthDataAccess> (fichier AuthDataAccess.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "AuthDataAccess.h"

// files
#include <fstream>
#include <sstream>

#include <filesystem>
namespace fs = std::filesystem;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
Credentials AuthDataAccess::findCredentials( string credentialsFilePath, string p_login, string p_password )
// Algorithme :
// Cette méthode lit le fichier de credentials et cherche un utilisateur
// avec le login et le mot de passe fournis. Si un utilisateur est trouvé,
// elle retourne un objet Credentials contenant les informations de l'utilisateur.
{
    ifstream file(credentialsFilePath);

    if (!file.is_open())
    {
        cerr << "Erreur lors de l'ouverture du fichier : " << credentialsFilePath << endl;
        return Credentials();
    }

    string line;
    // Lire l'en-tête
    getline(file, line);

    // lire les credentials
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        // lire le login
        getline(ss, token, ';');
        string login = token;

        // lire le mot de passe
        getline(ss, token, ';');
        string password = token;

        // lire le UserType
        getline(ss, token, ';');
        string userTypeString = token;

        // lire l'UserId
        string userId = "";
        if (getline(ss, token, ';')) {
            userId = token;
        }

        UserType userType;
        if (userTypeString == "ADMIN")
            userType = UserType::ADMIN;
        else if (userTypeString == "USER")
            userType = UserType::USER;
        else if (userTypeString == "PARTICULIER")
            userType = UserType::PARTICULIER;
        else if (userTypeString == "FOURNISSEUR")
            userType = UserType::FOURNISSEUR;
        else
            userType = UserType::UNDEFINED;

        if (login == p_login && password == p_password)
        {
            // Créer un objet Credentials avec les informations trouvées
            Credentials credentials(login, password, userType, userId);

            file.close();
            return credentials; // Retourner les credentials trouvés
        }
    }

    file.close();
    return Credentials(); // Retourner un objet Credentials vide si aucun match trouvé
} //----- Fin de findCredentials


//------------------------------------------------- Surcharge d'opérateurs
AuthDataAccess& AuthDataAccess::operator = ( const AuthDataAccess& unAuthDataAccess )
// Algorithme :
//
{
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
AuthDataAccess::AuthDataAccess ( const AuthDataAccess & unAuthDataAccess )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <AuthDataAccess>" << endl;
#endif
} //----- Fin de AuthDataAccess (constructeur de copie)


AuthDataAccess::AuthDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <AuthDataAccess>" << endl;
#endif
} //----- Fin de AuthDataAccess


AuthDataAccess::~AuthDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <AuthDataAccess>" << endl;
#endif
} //----- Fin de ~AuthDataAccess


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
