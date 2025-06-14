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

//------------------------------------------------------ Include personnel
#include "Statistics.h"
#include <algorithm>
#include <map>
#include <cmath>
#include <set>

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
int Statistics::analyzeSensor(string sensorID)
// Algorithme :
//
{
    // vérifie si l'utilisateur a les droits administrateur
    if (!authService->checkRequiredRole(UserType::ADMIN))
    {
        cerr << "Accès refusé : droits administrateur requis" << endl;
        return -1;
    }

    //cout << "[DEBUG] Analyse du capteur : " << sensorID << endl;

    Sensor* sensor = getSensorByID(sensorID);
    if (sensor == nullptr)
    {
        //cout << "[ERROR] Capteur introuvable : " << sensorID << endl;
        return -1;
    }

    vector<Sensor> neighbours = sensor->getSensorNeighbours(sensors, 60000);
    //cout << "[DEBUG] Capteurs voisins trouvés (" << neighbours.size() << ") : ";
    // for (auto& neighbour : neighbours)
    // {
    //     cout << neighbour.getId() << " ";
    // }
    // cout << endl;

    vector<Measurement> sensorMeasurements = sensor->getAllMeasurements();
    if (sensorMeasurements.empty())
    {
        //cout << "[WARNING] Aucune mesure trouvée pour ce capteur." << endl;
        return -1;
    }

    int totalComparisons = 0;
    int abnormalCount = 0;
    double anomalyThreshold = 0.2; // 20%


    for (auto& measurement : sensorMeasurements)
    {
        string attr_id = measurement.getAttr_id();
        double val = measurement.getValue();
        time_t ts = measurement.getTs();

        struct tm* tm_info = localtime(&ts);
        tm_info->tm_hour = 0; tm_info->tm_min = 0; tm_info->tm_sec = 0;
        time_t start = mktime(tm_info);
        tm_info->tm_hour = 23; tm_info->tm_min = 59; tm_info->tm_sec = 59;
        time_t end = mktime(tm_info);

        //cout << "[DEBUG] Mesure : " << attr_id << " = " << val << " à " << ctime(&ts);

        vector<double> neighbourValues;

        for (auto& neighbour : neighbours)
        {
            vector<Measurement> neighbour_measures = neighbour.getMeasurements(start, end);
            for (auto& neighbour_measure : neighbour_measures)
            {
                if (neighbour_measure.getAttr_id() == attr_id)
                {
                    neighbourValues.push_back(neighbour_measure.getValue());
                }
            }
        }

        if (neighbourValues.empty())
        {
            //cout << "[INFO] Aucun voisin n'a de mesure pour " << attr_id << " ce jour-là." << endl;
            continue;
        }

        double sum = 0;
        for (double v : neighbourValues) sum += v;
        double mean = sum / neighbourValues.size();

        

        double diff = fabs(val - mean);
        if (mean > 0) // évite division par zéro
        {
            
            double relativeDiff = diff / mean; 

            if (relativeDiff > anomalyThreshold)
            {
                abnormalCount++;
            }
            totalComparisons++;
        }

    }

    double anomalyRate = (double)abnormalCount / totalComparisons;

    //cout << "[RESULT] Anomaly rate: " << anomalyRate * 100 << "% over " << totalComparisons << " comparisons." << endl;

    if (anomalyRate > 0.3)  // 30% des comparaisons anormales
    {
        //cout << "[ALERTE] Capteur " << sensorID << " suspect : trop d'écarts détectés." << endl;
        return 0;
    }

    //cout << "[DEBUG] Aucune anomalie détectée." << endl;
    return 1;
}//----- Fin de analyzeSensor


// int Statistics::analyzeSensor( string sensorID )
// // Algorithme :
// //
// {
//     Sensor *sensor = getSensorByID(sensorID);
//     vector<Sensor> neighbours = sensor->getSensorNeighbours(sensors);
//     vector<Measurement> sensorMeasurements = sensor->getAllMeasurements();

//     if (sensorMeasurements.empty())
//     {
//         return -1;
//     }

//     for (auto& measurement : sensorMeasurements)
//     {
//         time_t ts = measurement.getTs( );
//         struct tm *tm_info = localtime(&ts);
//         tm_info->tm_hour = 0;
//         tm_info->tm_min  = 0;
//         tm_info->tm_sec  = 0;
//         time_t start = mktime(tm_info);

//         tm_info->tm_hour = 23;
//         tm_info->tm_min  = 59;
//         tm_info->tm_sec  = 59;
//         time_t end = mktime(tm_info);

//         for (auto& neighbour : neighbours)
//         {
//             vector<Measurement> neighbour_measures = neighbour.getMeasurements(start, end);
//             for (auto& neighbour_measure : neighbour_measures)
//             {
//                 double diff = measurement.getValue() - neighbour_measure.getValue();
//                 diff = (diff < 0) ? (-diff) : diff;

//                 if (diff > 0.2 * measurement.getValue())
//                 {
//                     return 0;
//                 }
//             }
//         }
//     }

//     return 1;
// } //----- Fin de analyzeSensor

vector<Measurement> Statistics::analyzeCleaner( string cleanerID, int radius )
// Algorithme :
//
{
    // vérifie si l'utilisateur a les droits fournisseur/admin pour la mesure des performances
    if (!authService->checkRequiredRole(UserType::FOURNISSEUR) && !authService->checkRequiredRole(UserType::ADMIN))
    {
        cerr << "Accès refusé : droits fournisseur requis" << endl;
        return {};
    }

    vector<Measurement> result;
    
    // Obtenir la position et la période d'activation du Cleaner
    Cleaner *cleaner = getCleanerByID(cleanerID);
    if (cleaner == nullptr)
    {
        cerr << "Erreur : Cleaner " << cleanerID << " non trouvé." << endl;
        return result;
    }

    time_t activationStart = cleaner->getStart();
    time_t activationEnd = cleaner->getEnd();
    vector<Sensor> nearbySensors = cleaner->getNeighbouringSensors(radius, sensors);

    if (nearbySensors.empty())
    {
        cerr << "Erreur : Aucun capteur à proximité du Cleaner." << endl;
        return result;
    }

    // Obtenir les mesures les plus proches
    vector<double> airQualityBefore = {0.0, 0.0, 0.0, 0.0};
    vector<double> airQualityAfter = {0.0, 0.0, 0.0, 0.0};
    int validCount = 0;

    for (auto& sensor : nearbySensors)
    {
        vector<Measurement> before = sensor.getClosestMeasurements(activationStart, -1);
        vector<Measurement> after = sensor.getClosestMeasurements(activationEnd, 1);
            
        if (!before.empty() && !after.empty())
        {
            for (int i = 0;  i < 4; i++)
            {
                airQualityBefore[i] += before[i].getValue();
                airQualityAfter[i] += after[i].getValue();
            }
            validCount++;
        }
    }

    if (validCount == 0)
    {
        cerr << "Erreur : Aucune mesure valide trouvée." << endl;
        return result;
    }

    // Calcule la moyenne et le pourcentage d'amélioration
    vector<double> avgBefore;
    vector<double> avgAfter;
    vector<Measurement> reference = nearbySensors[0].getClosestMeasurements(activationEnd, 1);

    for (int i = 0; i < 4; i++)
    {
        avgBefore.push_back(airQualityBefore[i] / validCount);
        avgAfter.push_back(airQualityAfter[i] / validCount);

        if (avgBefore[i] != 0)
        {
            Measurement measurement = Measurement(0, reference[i].getAttr_id(), reference[i].getAttr_unit(), reference[i].getAttr_desc(), (avgBefore[i] - avgAfter[i]) / avgBefore[i] * 100);
            result.push_back(measurement);
        }
    }

    return result;
} //----- Fin de analyzeCleaner

vector<Measurement> Statistics::computeZone( double lat, double lng, time_t period_start, time_t period_end, int radius, int radiusExtrapolation )
// Algorithme :
//
{
    // vérifie si l'utilisateur a les droits user/admin/particulier
    if (!authService->checkRequiredRole(UserType::USER) &&
        !authService->checkRequiredRole(UserType::ADMIN) &&
        !authService->checkRequiredRole(UserType::PARTICULIER))
    {
        cerr << "Accès refusé : droits utilisateurs/admin/fournisseur requis" << endl;
        return {};
    }

    // vérifie si le calcul doit être fait sur un jour et change les bornes en conséquence
    if (period_start  == period_end)
    {
        struct tm tm_info = *localtime(&period_start);
        tm_info.tm_hour = 0; tm_info.tm_min = 0; tm_info.tm_sec = 0;
        period_start = mktime(&tm_info);
        period_end = period_start + 24 * 60 * 60 - 1; // fin de la journée
    }

    // Si radius == 0 : on utilise la fonction extrapolateAQI
    if (radius == 0)
    {
        return extrapolateAQI(lat, lng, period_start, period_end, radiusExtrapolation);
    }

    // Sinon, recherche des capteurs se trouvant dans le rayon
    vector<Sensor> matchingSensors;
    vector<string> matchingSensorIds;
    for (auto& sensor : *sensors)
    {
        double d = sensor.distanceTo(lat, lng);
        if (d <= radius)
        {
            matchingSensors.push_back(sensor);
        }
    }

    // Aucun capteur trouvé dans le rayon
    if (matchingSensors.empty())
    {
        return {};
    }

    // Récupération des mesures pertinentes
    vector<Measurement> relevantMeasurements;
    for (auto& sensor : matchingSensors)
    {
        vector<Measurement> sensorMeasurements = sensor.getMeasurements(period_start, period_end);
        if (!sensorMeasurements.empty())
        {
            relevantMeasurements.insert(relevantMeasurements.end(), sensorMeasurements.begin(), sensorMeasurements.end());
            matchingSensorIds.push_back(sensor.getId());
        }
    }

    if (relevantMeasurements.empty())
    {
        // Aucune mesure disponible
        return {};
    }

    // Agrégation des mesures par type
    // aggregated[type] = { somme, nombre de mesures }
    map<string, pair<double, int>> aggregated;

    // Stocke les infos associées au type : { unité, description }
    map<string, pair<string, string>> typeInfo;

    for (auto& m : relevantMeasurements)
    {
        string type = m.getAttr_id();
        aggregated[type].first += m.getValue();
        aggregated[type].second += 1;

        if (typeInfo.find(type) == typeInfo.end())
        {
            typeInfo[type] = make_pair(m.getAttr_unit(), m.getAttr_desc());
        }
    }

    // Construction du vecteur résultat en calculant la moyenne pour chaque type
    vector<Measurement> result;
    for (auto& entry : aggregated)
    {
        double avg = entry.second.first / entry.second.second;
        Measurement m(period_start, entry.first, typeInfo[entry.first].first, typeInfo[entry.first].second, avg);

        result.push_back(m);
    }

    pointsManager->award(matchingSensorIds);

    return result;
} //----- Fin de computeZone

vector<Sensor> Statistics::compareSensors( string sensorId, time_t period_start, time_t period_end )
// Algorithme :
//
{
    // vérifie si l'utilisateur a les droits user
    if (!authService->checkRequiredRole(UserType::USER) &&!authService->checkRequiredRole(UserType::ADMIN) )
    {
        cerr << "Accès refusé : droits utilisateur requis" << endl;
        return {};
    }

    vector<Sensor> result;

    Sensor *sensorRef = getSensorByID(sensorId);
    if (sensorRef == nullptr)
    {
        cerr << "Erreur : Capteur " << sensorId << " non trouvé." << endl;
        return result;
    }

    vector<Measurement> refMeasurements = sensorRef->getMeasurements(period_start, period_end);
    if (refMeasurements.empty())
    {
        return result;
    }

    // Stockage temporaire des scores
    vector<pair<Sensor, double>> scoredSensors;

    for (Sensor& s : *sensors)
    {
        if (s.getId() == sensorId)
        {
            continue;
        }

        vector<Measurement> otherMeasurements = s.getMeasurements(period_start, period_end);
        if (otherMeasurements.size() != refMeasurements.size())
        {
            continue;
        }

        double totalDiff = 0.0;
        for (size_t i = 0; i < refMeasurements.size(); ++i)
        {
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

    for (const auto& entry : scoredSensors)
    {
        result.push_back(entry.first);
    }

    return result;
} //----- Fin de compareSensors

vector<Measurement> Statistics::extrapolateAQI(double lat, double lng, time_t period_start, time_t period_end, int radiusExtrapolation)
// Algorithme :
//
{
    vector<Measurement> result;
    vector<Measurement> exactMeasures;
    vector<vector<Measurement>> weightedMeasures;
    vector<Sensor> weightedSensors;
    map<string, pair<string, string>> allTypes;

    for (auto& sensor : *sensors)
    {
        // s'il y a un capteur à la position exacte on vérifie la liste des mesures
        if (sensor.getLat() == lat && sensor.getLng() == lng)
        {
            exactMeasures = sensor.getMeasurements(period_start, period_end);
            if (!exactMeasures.empty() && exactMeasures[0].getTs() == period_start && exactMeasures[exactMeasures.size() - 1].getTs() == period_end)
            {
                // on renvoie les mesures si la période est complète
                return exactMeasures;
            }

        }
        // sinon, on prend les mesures des capteurs les plus proches
        else if (sensor.distanceTo(lat, lng) <= radiusExtrapolation)
        {
            vector<Measurement> measurements = sensor.getMeasurements(period_start, period_end);
            weightedMeasures.push_back(measurements);
            weightedSensors.push_back(sensor);
        }
    }

    // S'il n'y a pas de mesures sur toute la période, on regroupe les mesures par jour et par type puis on extrapole les jours manquants.
    map<time_t, map<string, pair<double, int>>> dailyData;  // dailyData[day][type] = { somme, compte }
    for (auto& m : exactMeasures)
    {
        // calcul du jour pour la clé
        time_t ts = m.getTs();
        struct tm tm_info = *localtime(&ts);
        tm_info.tm_hour = 0; tm_info.tm_min = 0; tm_info.tm_sec = 0;
        time_t day = mktime(&tm_info);

        string type = m.getAttr_id();
        dailyData[day][type].first += m.getValue();
        dailyData[day][type].second++;
        allTypes[type] = make_pair(m.getAttr_unit(), m.getAttr_desc());
    }

    // Regroupement pondéré par jour et par type pour les capteurs proches
    map<time_t, map<string, pair<double, double>>> dailyWeighted;  // dailyWeighted[day][type] = { somme pondérée, somme des poids }
    if (!weightedMeasures.empty())
    {
        for (size_t i = 0; i < weightedMeasures.size(); i++)
        {
            double dist = weightedSensors[i].distanceTo(lat, lng);
            double weight = (dist == 0.0) ? 1.0 : 1.0 / dist;
            for (auto& m : weightedMeasures[i])
            {
                // calcul du jour pour la clé
                time_t ts = m.getTs();
                struct tm tm_info = *localtime(&ts);
                tm_info.tm_hour = 0; tm_info.tm_min = 0; tm_info.tm_sec = 0;
                time_t day = mktime(&tm_info);

                string type = m.getAttr_id();
                dailyWeighted[day][type].first += m.getValue() * weight;
                dailyWeighted[day][type].second += weight;
                allTypes[type] = make_pair(m.getAttr_unit(), m.getAttr_desc());
            }
        }
    }

    // Pour chaque jour de la période
    for (time_t day = period_start; day <= period_end; day += 24 * 60 * 60)
    {
        // Calcul du jour à minuit
        struct tm tm_date = *localtime(&day);
        tm_date.tm_hour = 0; tm_date.tm_min = 0; tm_date.tm_sec = 0;
        time_t dayMidnight = mktime(&tm_date);

        // Pour chaque type de mesure
        for (auto& type : allTypes)
        {
            double avg = 0;
            // Si mesures exactes disponibles pour ce type
            if (dailyData.count(dayMidnight) && dailyData[dayMidnight].count(type.first))  // count return un 0 ou 1
            {
                avg = dailyData[dayMidnight][type.first].first / dailyData[dayMidnight][type.first].second;
            }
            // Sinon, utiliser moyenne pondérée s'il y a des données
            else if (dailyWeighted.count(dayMidnight) &&
                     dailyWeighted[dayMidnight].count(type.first) &&
                     dailyWeighted[dayMidnight][type.first].second != 0)
            {
                avg = dailyWeighted[dayMidnight][type.first].first / dailyWeighted[dayMidnight][type.first].second;
            }

            // Création d'une mesure pour ce jour et ce type
            Measurement m(dayMidnight, type.first, type.second.first, type.second.second, avg);
            result.push_back(m);
        }
    }
    return result;
} //----- Fin de extrapolateAQI

Sensor * Statistics::getSensorByID( string id )
{
    vector<Sensor>::iterator sensor_it;
    Sensor * res = nullptr;
    for (sensor_it = sensors->begin(); sensor_it != sensors->end() && sensor_it->getId() != id ; sensor_it++);
    if (sensor_it != sensors->end())
    {
        res = &(*sensor_it);
    }

    return res;
} //----- Fin de getSensorByID

Cleaner * Statistics::getCleanerByID( string id )
{
    vector<Cleaner>::iterator cleaner_it;
    Cleaner * res = nullptr;
    for (cleaner_it = cleaners->begin(); cleaner_it != cleaners->end() && cleaner_it->getId() != id ; cleaner_it++);
    if (cleaner_it != cleaners->end())
    {
        res = &(*cleaner_it);
    }
    
    return res;
} //----- Fin de getCleanerByID


//------------------------------------------------- Surcharge d'opérateurs
Statistics& Statistics::operator = ( const Statistics& unStatistics )
// Algorithme :
//
{
    if (this != &unStatistics)
    {
        this->sensors = unStatistics.sensors;
        this->cleaners = unStatistics.cleaners;
        this->authService = unStatistics.authService;
    }

    return *this;
} //----- Fin de operator =


//-------------------------------------------- Constructeurs - destructeur
Statistics::Statistics( const Statistics & unStatistics )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de copie de <Statistics>" << endl;
#endif
    this->sensors = unStatistics.sensors;
    this->cleaners = unStatistics.cleaners;
    this->pointsManager = unStatistics.pointsManager;
    this->authService = unStatistics.authService;
} //----- Fin de Statistics (constructeur de copie)


Statistics::Statistics( vector<Sensor> *p_sensors, vector<Cleaner> *p_cleaners, PointsManager *p_pointsManager, AuthService *p_authService )
// Algorithme :
//
: sensors(p_sensors), cleaners(p_cleaners), pointsManager(p_pointsManager), authService(p_authService)
{
#ifdef MAP
    cout << "Appel au constructeur de <Statistics>" << endl;
#endif
} //----- Fin de Statistics


Statistics::~Statistics( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Statistics>" << endl;
#endif
    
} //----- Fin de ~Statistics


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
