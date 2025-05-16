/*************************************************************************
PointsManager  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//- Réalisation de la classe <PointsManager> (fichier PointsManager.cpp) -

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

//------------------------------------------------------ Include personnel
#include "PointsManager.h"


//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
bool PointsManager::award(list<string> sensorsUsed)
{
    std::ifstream infile("particulierData.csv");
    vector<string> lines;
    string line;

    bool updated = false;

    for (auto& s :sensorsUsed)
    {
        // Read all lines
        while (getline(infile, line)) {
            stringstream ss(line);
            string id, lat, lng, points;
            getline(ss, id, ',');
            getline(ss, lat, ',');
            getline(ss, lng, ',');
            getline(ss, points, ',');



            int award = stoi(points);
            if (id == s) {
                stringstream updatedLine;
                updatedLine << id << "," << lat << "," << lng << "," << award + 1;
                lines.push_back(updatedLine.str());
                updated = true;
            } else {
                lines.push_back(line);
            }
        }

        infile.close();

        if (!updated) {
            std::cerr << "Sensor ID not found in ParticulierData : " << s << std::endl;
            return;
        }

        // Write all lines back to file
        std::ofstream outfile("particulierData.csv");
        for (const auto& l : lines) {
            outfile << l << "\n";
        }

        outfile.close();
        

    }
    
    
}
// Algorithme :
//
//{
//} //----- Fin de award

int PointsManager::getPoints(string userId)
{
}
// Algorithme :
//
//{
//} //----- Fin de getPoints


//------------------------------------------------- Surcharge d'opérateurs
PointsManager& PointsManager::operator = ( const PointsManager& unPointsManager )
// Algorithme :
//
{
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
PointsManager::PointsManager ( const PointsManager & unPointsManager )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <PointsManager>" << endl;
#endif
} //----- Fin de PointsManager (constructeur de copie)


PointsManager::PointsManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <PointsManager>" << endl;
#endif
} //----- Fin de PointsManager


PointsManager::~PointsManager ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <PointsManager>" << endl;
#endif
} //----- Fin de ~PointsManager


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
