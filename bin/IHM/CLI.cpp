/*************************************************************************
CLI  -  description todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---------- Réalisation du module <CLI> (fichier CLI.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <iostream>

using namespace std;
//------------------------------------------------------ Include personnel
#include "../DataAccess/DataLoader.h"
#include "../Authentification/UserType.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//---------------------------------------------------- Variables statiques

//------------------------------------------------------ Fonctions privées


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques
void testDataLoader()
// Algorithme :
//
{
    DataLoader loader;

    // Charger les capteurs
    vector<Sensor>* sensors = loader.loadSensor("../data", UserType::USER);
    if (sensors)
    {
        cout << "Nombre de capteurs chargés : " << sensors->size() << endl;
        if(!sensors->empty())
        {
			cout << "Liste des capteurs : " << endl;
			for (auto& sensor : *sensors)
			{
            	cout << "ID : " << sensor.getId() << ", lat : " << sensor.getLat() << ", lng : " << sensor.getLng()
					 << ", userId : " << sensor.getUserId() << endl;
				cout << "Mesures : " << endl;
				for (auto& measure : sensor.getAllMeasurements())
                {
                    time_t ts = measure.getTs();
                    cout << "date : " << ctime(&ts) << ", attr_id : " << measure.getAttr_id() << ", attr_unit : "
					<< measure.getAttr_unit() << ", attr_desc : " << measure.getAttr_desc() << ", value : " << measure.getValue() << endl;
                }
				cout << endl;
			}
        }
    }
    else
    {
        cout << "Aucun capteur n'a été chargé." << endl;
    }

    // Charger les cleaners
    vector<Cleaner>* cleaners = loader.loadCleaner("../data", UserType::USER);
    if (cleaners)
    {
        cout << "Nombre de cleaners chargés : " << cleaners->size() << endl;
        if(!cleaners->empty())
        {
			cout << "Liste des cleaners : " << endl;
			for (auto& cleaner : *cleaners)
			{
				time_t start = cleaner.getStart();
				time_t end = cleaner.getEnd();

            	cout << "ID : " << cleaner.getId() << ", lat : " << cleaner.getLat() << ", lng : " << cleaner.getLng()
					 << ", start : " << ctime(&start) << ", stop : " << ctime(&end) << endl;
			}
        }
    }
    else
    {
        cout << "Aucun cleaner n'a été chargé." << endl;
    }
} //----- fin de testDataLoader


void run()
// Algorithme :
//
{
} //----- fin de run

int main(int argc, char *argv[])
// Algorithme :
//
{
    run();
	testDataLoader();
    return 0;
} //----- fin de main

