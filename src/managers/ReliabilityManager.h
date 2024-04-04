//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_RELIABILITYMANAGER_H
#define DA_WATER_SUPPLY_RELIABILITYMANAGER_H


#include "models/Graph.h"
#include "FlowManager.h"

class ReliabilityManager {
private:
    Graph graph;
    vector<CityMetrics> originalMetrics;

public:
    ReliabilityManager();

    CityMetrics getCityMetrics(string code);

    vector<pair<std::string, double>> evaluateReservoirImpact(string code);

    vector<pair<string, double>> evaluateStationImpact(string code);

    vector<pair<string, double>> evaluatePipeImpact(string source, string dest);

    vector<pair<pair<string, string>, double>> evaluateCityImpactByPipes(string code);
};

#endif //DA_WATER_SUPPLY_RELIABILITYMANAGER_H
