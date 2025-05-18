/*************************************************************************
DataLoader  -  Charge les données de la base de données dans
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---- Réalisation de la classe <DataLoader> (fichier DataLoader.cpp) ----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "DataLoader.h"
#include <unordered_map>

// time
#include <ctime>
#include <iomanip>

// files
#include <fstream>
#include <sstream>

#include <filesystem>
namespace fs = std::filesystem;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
vector<Sensor>* DataLoader::loadSensor( string databasePath, UserType userType )
// Algorithme : charge les données des capteurs à partir des fichiers csv attributes,
// measurements, sensors et users contenu dans le dossier data. Les attributs sont
// chargés en premier et doivent garder le même nom pour un chargement plus efficace
// des mesures. todo : adapter pour les userType
{
    // Créer une map des capteurs déjà chargés avec leur id en valeur et l'id en clé
    unordered_map<string, int> sensorsMap;
    unordered_map<string, vector<string>> measurementsAttributesMap;

    bool sensorsFound = false;
    bool measurementsFound = false;
    bool usersFound = false;
    bool attributesFound = false;

    ifstream file(databasePath + "/attributes.csv");

    if (file.is_open())
    {
        attributesFound = true;
        string line;

        // Charger les attributs
        while (getline(file, line))
        {
            stringstream ss(line);
            string token;

            // Extraire l'id
            getline(ss, token, ';');
            string attributeId = token;

            // Extraire l'unité
            getline(ss, token, ';');
            string attributeUnit = token;

            // Extraire la description
            getline(ss, token, ';');
            string attributeDesc = token;

            // Ajouter l'attribut à la map
            vector<string> attributeInfo = {attributeUnit, attributeDesc};
            measurementsAttributesMap[attributeId] = attributeInfo;
        }
        file.close();
    }
    else
    {
        cerr << "Aucun fichier d'attributs trouvé dans la base de données." << endl;
        return nullptr;
    }

    // Parcourir le dossier data et charger les fichiers
    for (const auto& entry : fs::directory_iterator(databasePath))
    {
        string filePath = entry.path().string();
        ifstream file(filePath);

        if (file.is_open())
        {
            string line;
            if (filePath.find("sensors") != string::npos)
            {
                sensorsFound = true;
                // Charger les capteurs
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string token;

                    // Extraire l'id
                    getline(ss, token, ';');
                    string sensorId = token;

                    // Extraire la latitude
                    getline(ss, token, ';');
                    double lat = stod(token);

                    // Extraire la longitude
                    getline(ss, token, ';');
                    double lng = stod(token);

                    // Vérifier si le capteur existe déjà
                    if (sensorsMap.find(sensorId) == sensorsMap.end())
                    {
                        sensors.emplace_back();
                        sensors.back().setId(sensorId);
                        sensors.back().setLat(lat);
                        sensors.back().setLng(lng);
                        sensorsMap[sensorId] = sensors.size() - 1;
                    }
                    else
                    {
                        int ind = sensorsMap[sensorId];
                        sensors[ind].setLat(lat);
                        sensors[ind].setLng(lng);
                    }
                }
            }
            else if (filePath.find("measurements") != string::npos)
            {
                measurementsFound = true;
                // Charger les mesures
                unordered_map<string, vector<Measurement>> measurementsMap;

                while (getline(file, line))
                {
                    stringstream ss(line);
                    string token;

                    // Extraire le timestamp
                    getline(ss, token, ';');

                    // convertir la chaîne de caractères en temps
                    tm tmDate = {};
                    istringstream ssDate(token);
                    ssDate >> get_time(&tmDate, "%Y-%m-%d %H:%M:%S");

                    time_t ts = mktime(&tmDate);

                    // Extraire le sensorId
                    getline(ss, token, ';');
                    string sensorId = token;

                    // Extraire l'attribute id
                    getline(ss, token, ';');
                    string attributeId = token;

                    // Obtenir les unités et la description de l'attribut
                    string attributeUnit = measurementsAttributesMap[attributeId][0];
                    string attributeDesc = measurementsAttributesMap[attributeId][1];

                    // Extraire la valeur
                    getline(ss, token, ';');
                    int value = stoi(token);

                    // ajoute les mesures à la map
                    measurementsMap[sensorId].emplace_back(ts, attributeId, attributeUnit, attributeDesc, value);
                }

                for (auto& measurements : measurementsMap)
                {
                    string sensorId = measurements.first;
                    vector<Measurement> sensorMeasurements = measurements.second;

                    // Vérifier si le capteur existe déjà
                    if (sensorsMap.find(sensorId) == sensorsMap.end())
                    {
                        sensors.emplace_back();
						sensors.back().setId(sensorId);
                        sensors.back().setMeasurements(sensorMeasurements);
                        sensorsMap[sensorId] = sensors.size() - 1;
                    }
                    else
                    {
                        int ind = sensorsMap[sensorId];
                        sensors[ind].setMeasurements(sensorMeasurements);
                    }
                }
            }
            else if (filePath.find("users") != string::npos)
            {
                while (getline(file, line))
                {
                    usersFound = true;
                    // Charger les userID des particuliers
                    stringstream ss(line);
                    string token;

                    // Extraire le userId
                    getline(ss, token, ';');
                    string userId = token;

                    // Extraire le sensorid
                    getline(ss, token, ';');
                    string sensorId = token;

                    // Vérifier si le capteur existe déjà
                    if (sensorsMap.find(sensorId) == sensorsMap.end())
                    {
                        sensors.emplace_back();
                        sensors.back().setUserId(userId);
                        sensorsMap[sensorId] = sensors.size() - 1;
                    }
                    else
                    {
                        int ind = sensorsMap[sensorId];
                        sensors[ind].setUserId(userId);
                    }
                }
            }

            file.close();
        } else {
            cerr << "Erreur lors de l'ouverture du fichier : " << filePath << endl;
        }
    }

    if (sensorsFound && measurementsFound && usersFound && attributesFound)
    {
        return &sensors;
    }
    else
    {
        if (!sensorsFound)
            cerr << "Aucun fichier de capteurs trouvé dans la base de données." << endl;
        if (!measurementsFound)
            cerr << "Aucun fichier de mesures trouvé dans la base de données." << endl;
        if (!usersFound)
            cerr << "Aucun fichier d'utilisateurs trouvé dans la base de données." << endl;

        return nullptr;
    }
} //----- Fin de loadSensor

vector<Cleaner>* DataLoader::loadCleaner( string databasePath, UserType userType )
// Algorithme : charge les données des cleaners à partir du fichier csv contenu
// dans le dossier data (cleaners). todo : adapter pour les userType
{
    for (const auto& entry : fs::directory_iterator(databasePath))
    {
        string filePath = entry.path().string();
        ifstream file(filePath);

        if (filePath.find("cleaners") != string::npos)
        {
            if (file.is_open())
            {
                string line;
                // Charger les cleaners
                while (getline(file, line))
                {
                    stringstream ss(line);
                    string token;

                    // Extraire l'id
                    getline(ss, token, ';');
                    string sensorId = token;

                    // Extraire la latitude
                    getline(ss, token, ';');
                    double lat = stod(token);

                    // Extraire la longitude
                    getline(ss, token, ';');
                    double lng = stod(token);

                    // Extraire la date de début
                    getline(ss, token, ';');

                    // convertir la chaîne de caractères en temps
                    tm tmDate = {};
                    istringstream ssDate1(token);
                    ssDate1 >> get_time(&tmDate, "%Y-%m-%d %H:%M:%S");

                    time_t start = mktime(&tmDate);

                    // Extraire la date de fin
                    getline(ss, token, ';');

                    // convertir la chaîne de caractères en temps
                    tmDate = {};
                    istringstream ssDate2(token);
                    ssDate2 >> get_time(&tmDate, "%Y-%m-%d %H:%M:%S");

                    time_t end = mktime(&tmDate);

                    // emplace_back pour éviter une copie inutile
                    cleaners.emplace_back(sensorId, lat, lng, start, end);
                }

                file.close();
                return &cleaners;
            }
            else
            {
                cerr << "Erreur lors de l'ouverture du fichier : " << filePath << endl;
                return nullptr;
            }
        }
    }

    return nullptr;
} //----- Fin de loadCleaner


//------------------------------------------------- Surcharge d'opérateurs
DataLoader& DataLoader::operator = ( const DataLoader& unDataLoader )
// Algorithme : les attributs sont des vecteurs donc la copie est automatique
//
{
    if (this != &unDataLoader)
    {
        this->sensors = unDataLoader.sensors;
        this->cleaners = unDataLoader.cleaners;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
DataLoader::DataLoader( const DataLoader & unDataLoader )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <DataLoader>" << endl;
#endif
    this->sensors = unDataLoader.sensors;
    this->cleaners = unDataLoader.cleaners;
} //----- Fin de DataLoader (constructeur de copie)

DataLoader::DataLoader( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <DataLoader>" << endl;
#endif
} //----- Fin de DataLoader

DataLoader::~DataLoader ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DataLoader>" << endl;
#endif
} //----- Fin de ~DataLoader


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
