/*************************************************************************
UserDataAccess  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <UserDataAccess> (fichier UserDataAccess.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//------------------------------------------------------ Include personnel
#include "UserDataAccess.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques


int UserDataAccess::loadUserPoints(string userId)
{
    ifstream file("ParticulierData.csv");
    if (!file.is_open())
    {
        cerr << "Erreur d'ouverture du fichier userPoints.csv" << endl;
        return -1; // Erreur d'ouverture du fichier
    }
    string line;
    while(getline(file,line)){
        vector<string> row;
        stringstream ss(line);
        string cell;
        while(getline(ss, cell, ';')){
            row.push_back(cell);
        }

        if (row.size() >= 3) {
                string currentUserId = row[0];
                if (currentUserId == userId) {
                    int points = stoi(row[1]);
                    file.close();
                    return points;
                }
            }
    }

    file.close();
    return -1;  // Usuario no encontrado
    
}
// Algorithme :
//
//{
//} //----- Fin de loadUserPoints

int UserDataAccess::updateUserPoints(string userId) {
    // Ouverture du fichier
    ifstream inFile("ParticulierData.csv");
    if (!inFile.is_open()) {
        cerr << "Erreur d'ouverture du fichier ParticulierData.csv" << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool userFound = false;
    int newPoints = 0;

    // Leecture de chaque ligne du fichier
    while (getline(inFile, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row.push_back(cell);
        }

        if (row.size() >= 3 && row[0] == userId) {
            if (row[2] == "true") {
                inFile.close();
                return -1; // User is excluded
            }
            newPoints = stoi(row[1]) + 10;
            line = userId + ";" + to_string(newPoints) + ";" + row[2];
            userFound = true;
        }
        lines.push_back(line);
    }
    inFile.close();

   //Utilisateur non trouvé, on l'ajoute avec 10 points
    if (!userFound) {
        lines.push_back(userId + ";10;false");
        newPoints = 10;
    }

    // Ouverture du fichier en écriture
    ofstream outFile("ParticulierData.csv");
    if (!outFile.is_open()) {
        cerr << "Erreur d'écriture du fichier ParticulierData.csv" << endl;
        return -1;
    }

    // Ecrire l'en-tête si le fichier est vide
    if (lines.empty()) {
        outFile << "userId;points;excluded\n";
    }

    // Ecriture de chaque ligne dans le fichier
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    return newPoints; // Retourne les nouveaux points de l'utilisateur
}
// Algorithme :
//
//{
//} //----- Fin de updateUserPoints

vector<string> UserDataAccess::loadExcludedUsers()
{
    // Ouverture du fichier
    ifstream inFile("ParticulierData.csv");
    if (!inFile.is_open()) {
        cerr << "Erreur d'ouverture du fichier ParticulierData.csv" << endl;
        return vector<string>(); // Retourne un vecteur vide en cas d'erreur
    }

    vector<string> excludedUsers;
    string line;

    // Leecture de chaque ligne du fichier
    while (getline(inFile, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row.push_back(cell);
        }

        if (row.size() >= 3 && row[2] == "true") {
            excludedUsers.push_back(row[0]);
        }
    }

    if (inFile.tellg() == 0) {
        cerr << "Le fichier ParticulierData.csv est vide." << endl;
        return vector<string>(); // Retourne un vecteur vide si le fichier est vide
    }

    inFile.close();
    return excludedUsers;
}
// Algorithme :
//
//{
//} //----- Fin de loadExcludedUsers

int UserDataAccess::addExcludedUser(string userId)
{
    // Ouverture du fichier
    ifstream inFile("ParticulierData.csv");
    if (!inFile.is_open()) {
        cerr << "Erreur d'ouverture du fichier ParticulierData.csv" << endl;
        return -1;
    }

    vector<string> lines;
    string line;

    // Leecture de chaque ligne du fichier
    while (getline(inFile, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row.push_back(cell);
        }

        if (row.size() >= 3 && row[0] == userId) {
            if (row[2] == "true") {
                inFile.close();
                return 0; // User is excluded
            }
            line = userId + ";" + row[1] + ";" + "true";
        }
        lines.push_back(line);
    }
    inFile.close();


    // Ouverture du fichier en écriture
    ofstream outFile("ParticulierData.csv");
    if (!outFile.is_open()) {
        cerr << "Erreur d'écriture du fichier ParticulierData.csv" << endl;
        return -1;
    }

    // Ecrire l'en-tête si le fichier est vide
    if (lines.empty()) {
        outFile << "userId;points;excluded\n";
        line = userId + ";" + "0" + ";" + "true";
        lines.push_back(line);
    }

    // Ecriture de chaque ligne dans le fichier
    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();

    return 1; 

}
// Algorithme :
//
//{
//} //----- Fin de addExcludedUser


//------------------------------------------------- Surcharge d'opérateurs
UserDataAccess& UserDataAccess::operator = ( const UserDataAccess& unUserDataAccess )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
UserDataAccess::UserDataAccess ( const UserDataAccess & unUserDataAccess )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <UserDataAccess>" << endl;
#endif
} //----- Fin de UserDataAccess (constructeur de copie)


UserDataAccess::UserDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UserDataAccess>" << endl;
#endif
} //----- Fin de UserDataAccess


UserDataAccess::~UserDataAccess ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UserDataAccess>" << endl;
#endif
} //----- Fin de ~UserDataAccess


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
