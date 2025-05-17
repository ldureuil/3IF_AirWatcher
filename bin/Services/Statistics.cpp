/*************************************************************************
Statistics  -  todo
                             -------------------
    début                : 16/05/2025
*************************************************************************/

//---- Réalisation de la classe <Statistics> (fichier Statistics.cpp) ----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <algorithm>

//------------------------------------------------------ Include personnel
#include "Statistics.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Statistics::analyzeSensor(string sensorID)
// Algorithme :
//
{
    Sensor sensor = getSensorByID( sensorID );
    vector<Sensor> neighbours = sensor.getSensorNeighbours( this->sensors );
    vector<Measurement> sensorMeasurements = sensor.getAllMeasurement( );
    if (sensorMeasurements.empty()) {
        return -1;
    }
    for ( vector<Measurement>::iterator measurement_it = sensorMeasurements.begin() ; measurement_it != sensorMeasurements.end() ; ++measurement_it )
    {
        time_t date = measurement_it->getTs( );
        for ( vector<Sensor>::iterator neighbour_it = neighbours.begin() ; neighbour_it != neighbours.end() ; ++neighbour_it )
        {
            vector<Measurement> neigh_meas = neighbour_it->getMeasurements(date - 12*60*60, date + 12*60*60);
            for ( vector<Measurement>::iterator neigh_meas_it = neigh_meas.begin() ; neigh_meas_it != neigh_meas.end() ; ++neigh_meas_it )
            {
                double diff = measurement_it->getValue() - neigh_meas_it->getValue();
                diff = (diff < 0) ? (-diff) : diff;
                if (diff > 0.2 * measurement_it->getValue())
                {
                    return 0;
                }
            }
        }
    }

    return 1;
} //----- Fin de analyzeSensor

vector<int> Statistics::analyzeCleaner(string cleanerID)
// Algorithme :
//
{
    vector<int> result;
    int radius = 100;
    
    // Obtenir la position et la période d'activation du Cleaner
    Cleaner cleaner = this->getCleanerByID( cleanerID );
    if (&cleaner == nullptr)
    {
        //cerr
        return result;
    }
    
    double cleanerLat =cleaner.getLat();
    double cleanerLng = cleaner.getLng();
    time_t activationStart = cleaner.getStart();
    time_t activationEnd = cleaner.getEnd();
    vector<Sensor> nearbySensors = cleaner.getNeighbouringSensors(radius, sensors );


    if (nearbySensors.empty())
    {
        //cerr
        return result;
    }

    // Obtenir les mesures les plus proches
    vector<double> airQualityBefore;
    vector<double> airQualityAfter;
    int validCount = 0;

    for (auto& sensor : nearbySensors)
    {
        vector<Measurement> before =sensor.getClosestMeasurements(activationStart, -1);
        vector<Measurement> after = sensor.getClosestMeasurements(activationEnd, 1);
            
        if (!before.empty() && !after.empty())
        {
            int i;
            for (i=0;  i<4; i++)
            {
                airQualityBefore[i] += before[i].getValue();
                airQualityAfter[i] += after[i].getValue();
                validCount++;

                if (validCount == 0)
                {
                    //cerr
                    return result;
                }
            
            }
        }
    }

    // Calcul la moyenne et le pourcentage dâ€™amÃ©lioration
    double avgBefore[4];
    double avgAfter[4];
    vector<int> improvePercent;
    int i;
    for ( i = 0; i < 4; i++)
    {
        avgBefore[i] = airQualityBefore[i] / validCount;
        avgAfter[i] = airQualityAfter[i] / validCount;

        if (avgBefore[i] != 0)
            improvePercent[i] = (avgBefore[i] - avgAfter[i]) / avgBefore[i] * 100;
        else
        {
            improvePercent[i] = 0;
    
        }
            
    }
        
    return improvePercent;
} //----- Fin de analyzeCleaner

vector<Measurement> Statistics::computeZone(double lat, double lng, time_t period_start, time_t period_end, int radius)
// Algorithme :
//
{

} //----- Fin de computeZone

vector<Sensor> Statistics::compareSensors(string sensorId, time_t period_start, time_t period_end)
// Algorithme :
//
{

    vector<Sensor> result;

    if (sensors == nullptr) {
        cerr << "Liste des capteurs non initialisée." << endl;
        return result;
    }

    Sensor* sensorRef = nullptr;


    *sensorRef = getSensorByID(sensorId);

    

    if (sensorRef == nullptr) {
        cerr << "Capteur " << sensorId << " non trouvé." << endl;
        return result;
    }

    vector<Measurement> refMeasurements = sensorRef->getMeasurements(period_start, period_end);
    if (refMeasurements.empty()) return result;

    // Stockage temporaire des scores
    vector<pair<Sensor, double>> scoredSensors;

    for (Sensor& s : *sensors) {
        if (s.getId() == sensorId) continue;

        vector<Measurement> otherMeasurements = s.getMeasurements(period_start, period_end);
        if (otherMeasurements.size() != refMeasurements.size()) continue;

        double totalDiff = 0.0;
        for (size_t i = 0; i < refMeasurements.size(); ++i) {
            totalDiff += abs(refMeasurements[i].getValue() - otherMeasurements[i].getValue());
        }

        double avgDiff = totalDiff / refMeasurements.size();
        scoredSensors.push_back(make_pair(s, avgDiff));
    }

    // Tri des capteurs par similarité croissante
    sort(scoredSensors.begin(), scoredSensors.end(),
        [](const pair<Sensor, double>& a, const pair<Sensor, double>& b) {
            return a.second < b.second;
        });

    for (const auto& entry : scoredSensors) {
        result.push_back(entry.first);
    }

    return result;

  

} //----- Fin de compareSensors

vector<Measurement> Statistics::extrapolateAQI(double lat, double lng, time_t period_start, time_t period_end)
{
}
// Algorithme :
//
//{
//} //----- Fin de extrapolateAQI

Sensor Statistics::getSensorByID ( string id )
{
    vector<Sensor>::iterator sensor_it = this->sensors->begin();
    while (sensor_it != this->sensors->end() && sensor_it->getId() != id) {
        ++sensor_it;
    }
    return *sensor_it;
}

Cleaner Statistics::getCleanerByID ( string id )
{
    vector<Cleaner>::iterator cleaner_it = this->cleaners->begin();
    while (cleaner_it != this->cleaners->end() && cleaner_it->getId() != id) {
        ++cleaner_it;
    }
    return *cleaner_it;
}

//------------------------------------------------- Surcharge d'opérateurs
Statistics& Statistics::operator = ( const Statistics& unStatistics )
// Algorithme :
//
{
    if (this != &unStatistics)
    {
        this->sensors = unStatistics.sensors;
        this->cleaners = unStatistics.cleaners;
    }
    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Statistics::Statistics ( const Statistics & unStatistics )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Statistics>" << endl;
#endif
    this->sensors = unStatistics.sensors;
    this->cleaners = unStatistics.cleaners;
} //----- Fin de Statistics (constructeur de copie)


Statistics::Statistics ( vector<Sensor> *p_sensors, vector<Cleaner> *p_cleaners )
    : sensors(p_sensors), cleaners(p_cleaners)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Statistics>" << endl;
#endif
} //----- Fin de Statistics


Statistics::~Statistics ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Statistics>" << endl;
#endif
} //----- Fin de ~Statistics


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
