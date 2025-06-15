/*************************************************************************
UserDataAccess  -  Permet de charger et modifier les informations des particuliers
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <UserDataAccess> (fichier UserDataAccess.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
//------------------------------------------------------ Include personnel
#include "UserDataAccess.h"
using namespace std;

//------------------------------------------------------------- Constantes
const int POINT_ATTRIBUTION = 1;
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

bool UserDataAccess::initializeCSVFile( string filename )
// Algorithme : Vérifie si le fichier existe déjà, sinon le crée.
{
    std::ifstream testFile(filename);
    if (testFile.good())
    {
        testFile.close();
        return true;  // Le fichier existe déjà
    }
    
    std::ofstream newFile(filename);
    if (!newFile)
    {
        return false;  // Erreur lors de la création du fichier
    }
    
    newFile.close();
    return true;
}

vector<ParticulierData> UserDataAccess::loadParticulierData( string path )
// Algorithme :
// Vérifier si l'ID utilisateur correspond à celui recherché en parcourant le fichier ParticulierData.csv
// Si trouvé, retourner les points de l'utilisateur
// Retourner -1 si l'utilisateur n'est pas trouvé
{
    ifstream inFile(path);

    if (!inFile.is_open())
    {
        cerr << "Erreur d'ouverture du fichier ParticulierData.csv" << endl;
        return vector<ParticulierData>(); // Retourner un vecteur vide en cas d'erreur
    }

    // Vérifier si le fichier est vide
    inFile.seekg(0, ios::end);
    if (inFile.tellg() == 0)
    {
        cerr << "Le fichier ParticulierData.csv est vide." << endl;
        return vector<ParticulierData>(); // Retourner un vecteur vide si fichier vide
    }
    inFile.seekg(0, ios::beg); // Revenir au début

    vector<ParticulierData> particulierDataList;
    ParticulierData particulierData;
    string line;

    // Lire chaque ligne du fichier
    while (getline(inFile, line))
    {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';'))
        {
            row.push_back(cell);
        }
        // Ajouter chaque utilisateur

        if (row.size() >= 3)
        {
            particulierData = ParticulierData(row[0], stoi(row[1]), row[2] == "1");
            particulierDataList.push_back(particulierData);
        }
    }

    inFile.close();
    return particulierDataList;
} //----- Fin de loadParticulierData

int UserDataAccess::updateUserPoints( string userId, string filename )
// Algorithme :
// Vérifier si l'ID utilisateur correspond à celui recherché en parcourant le fichier ParticulierData.csv
// Si trouvé, incrémenter les points de 1
// Si l'utilisateur n'est pas trouvé et/ou fichier n'est pas créé, l'ajouter avec 1 points
// Retourner les nouveaux points de l'utilisateur
{
    // Ouverture du fichier
    initializeCSVFile(filename);
    ifstream inFile(filename);
    if (!inFile.is_open())
    {
        cerr << "Erreur d'ouverture du fichier ParticulierData.csv" << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool userFound = false;
    int newPoints = 0;

    // Leecture de chaque ligne du fichier
    while (getline(inFile, line))
    {
        vector<string> row;
        stringstream ss(line);
        string cell;

        while (getline(ss, cell, ';'))
        {
            row.push_back(cell);
        }

        if (row.size() >= 3 && row[0] == userId)
        {
            if (row[2] == "true")
            {
                inFile.close();
                return -1; // User is excluded
            }
            newPoints = stoi(row[1]) + POINT_ATTRIBUTION ;
            line = userId + ";" + to_string(newPoints) + ";" + row[2];
            userFound = true;
        }
        lines.push_back(line);
    }
    inFile.close();

   //Utilisateur non trouvé, on l'ajoute avec 1 points
    if (!userFound)
    {
        lines.push_back(userId + ";"+ to_string(POINT_ATTRIBUTION) + ";false");
        newPoints = POINT_ATTRIBUTION;
    }

    // Ouverture du fichier en écriture
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Erreur d'écriture du fichier ParticulierData.csv" << endl;
        return -1;
    }

    // Ecriture de chaque ligne dans le fichier
    for (const auto& l : lines)
    {
        outFile << l << endl;
    }
    outFile.close();

    return newPoints; // Retourne les nouveaux points de l'utilisateur
}//----- Fin de updateUserPoints

int UserDataAccess::addExcludedUser( string userId, string filename )
// Algorithme :
// Vérifier si l'ID utilisateur correspond à celui recherché en parcourant le fichier ParticulierData.csv
// Si trouvé, vérifier le statut exclu
// Si trouvé, marquer comme exclu
// Si l'utilisateur n'est pas trouvé, l'ajouter avec le statut exclu
// Retourner 0 si déjà exclu, 1 si succès, -1 en cas d'erreur
{
    initializeCSVFile(filename);
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Erreur d'ouverture du fichier " << filename << endl;
        return -1;
    }

    vector<string> lines;
    string line;
    bool userFound = false;

    // Lecture du fichier
    while (getline(inFile, line))
    {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ';'))
        {
            row.push_back(cell);
        }

        if (row.size() >= 3 && row[0] == userId)
        {
            if (row[2] == "true")
            {
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
    if (!userFound)
    {
        line = userId + ";0;true";
        lines.push_back(line);
    }

    // Écriture dans le fichier
    ofstream outFile(filename);
    if (!outFile.is_open())
    {
        cerr << "Erreur d'écriture du fichier " << filename << endl;
        return -1;
    }

    for (const auto& l : lines)
    {
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
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
UserDataAccess::UserDataAccess( const UserDataAccess & unUserDataAccess )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <UserDataAccess>" << endl;
#endif
} //----- Fin de UserDataAccess (constructeur de copie)


UserDataAccess::UserDataAccess( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <UserDataAccess>" << endl;
#endif
} //----- Fin de UserDataAccess


UserDataAccess::~UserDataAccess( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <UserDataAccess>" << endl;
#endif
} //----- Fin de ~UserDataAccess


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
