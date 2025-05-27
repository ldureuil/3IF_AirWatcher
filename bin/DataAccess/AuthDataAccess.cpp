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
Credentials AuthDataAccess::findCredentials( string databasePath, string p_login, string p_password )
// Algorithme : Parcourt un fichier csv contenant credentials pour trouver les
// identifiants correspondants.
{
    for (const auto& entry : fs::directory_iterator(databasePath))
    {
        string filePath = entry.path().string();
        ifstream file(filePath);

        if (filePath.find("credentials") != string::npos)
        {
            if (file.is_open())
            {
                string line;
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

                    UserType userType;
                    if (userTypeString == "ADMIN")
                        userType = UserType::ADMIN;
                    else if (userTypeString == "USER")
                        userType = UserType::USER;
                    else if (userTypeString == "PARTICULIER")
                        userType = UserType::USER;
                    else if (userTypeString == "FOURNISSEUR")
                        userType = UserType::USER;
                    // pas besoin de else car on suppose que le fichier est bien formé

                    if (login == p_login && password == p_password)
                    {
                        // Créer un objet Credentials avec les informations trouvées
                        Credentials credentials(login, password, userType);

                        file.close();
                        return credentials; // Retourner les credentials trouvés
                    }
                }

                file.close();
                return Credentials(); // Retourner un objet Credentials vide si aucun match trouvé
            }
            else
            {
                cerr << "Erreur lors de l'ouverture du fichier : " << filePath << endl;
                return Credentials();
            }
        }
    }

    return Credentials();
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
