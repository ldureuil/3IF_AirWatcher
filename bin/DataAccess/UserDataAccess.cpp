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
// Algorithme : 
// Vérifier si l'ID utilisateur correspond à celui recherché en parcourant le fichier ParticulierData.csv
// Si trouvé, retourner les points de l'utilisateur
// Retourner -1 si l'utilisateur n'est pas trouvé
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
    
} //----- Fin de loadUserPoints



int UserDataAccess::updateUserPoints(string userId) 
// Algorithme :
// Vérifier si l'ID utilisateur correspond à celui recherché en parcourant le fichier ParticulierData.csv
// Si trouvé, incrémenter les points de 10
// Si l'utilisateur n'est pas trouvé et/ou fichier n'est pas créé, l'ajouter avec 10 points
// Retourner les nouveaux points de l'utilisateur
{
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
}//----- Fin de updateUserPoints

vector<string> UserDataAccess::loadExcludedUsers()
//Algorithme : 
// Retourne les utilisateurs exclus (vecteur) en parcourant le fichier ParticulierData.csv
// Retourne un vecteur vide si le fichier est vide, ou s'il n'y a pas des utilisateurs exclus ou en cas d'erreur
{
    ifstream inFile("ParticulierData.csv");
    if (!inFile.is_open()) {
        cerr << "Erreur d'ouverture du fichier ParticulierData.csv" << endl;
        return vector<string>(); // Retourner un vecteur vide en cas d'erreur
    }

    // Vérifier si le fichier est vide
    inFile.seekg(0, ios::end);
    if (inFile.tellg() == 0) {
        cerr << "Le fichier ParticulierData.csv est vide." << endl;
        return vector<string>(); // Retourner un vecteur vide si fichier vide
    }
    inFile.seekg(0, ios::beg); // Revenir au début

    vector<string> excludedUsers;
    string line;

    // Lire chaque ligne du fichier
    while (getline(inFile, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';')) {
            row.push_back(cell);
        }
        // Trouver les utilisateurs exclus
        if (row.size() >= 3 && row[2] == "true") {
            excludedUsers.push_back(row[0]);
        }
    }

    inFile.close();
    return excludedUsers;
}//----- Fin de loadExcludedUsers

int UserDataAccess::addExcludedUser(string userId)
// Algorithme :
// Vérifier si l'ID utilisateur correspond à celui recherché en parcourant le fichier ParticulierData.csv
// Si trouvé, vérifier le statut exclu
// Si trouvé, marquer comme exclu
// Si l'utilisateur n'est pas trouvé, l'ajouter avec le statut exclu
// Retourner 0 si déjà exclu, 1 si succès, -1 en cas d'erreur
{
    const string filename = "ParticulierData.csv";
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Erreur d'ouverture du fichier " << filename << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool userFound = false;
    bool userExcluded = false;

    // Lecture du fichier
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
                return 0; // Déjà exclu
            }
            // Marquer comme exclu
            row[2] = "true";
            line = row[0] + ";" + row[1] + ";" + row[2];
            userFound = true;
        }
        lines.push_back(line);
    }
    inFile.close();

    // Si l'utilisateur n'existe pas, l'ajouter
    if (!userFound) {
        line = userId + ";0;true";
        lines.push_back(line);
    }

    // Écriture dans le fichier
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Erreur d'écriture du fichier " << filename << endl;
        return -1;
    }

    // Écriture de l'en-tête
    outFile << "userId;points;excluded" << endl;

    for (const auto& l : lines) {
        outFile << l << endl;
    }

    outFile.close();
    return 1; // Succès
} //----- Fin de addExcludedUser


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
