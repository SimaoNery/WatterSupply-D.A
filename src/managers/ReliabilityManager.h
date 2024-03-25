//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_RELIABILITYMANAGER_H
#define DA_WATER_SUPPLY_RELIABILITYMANAGER_H


#include "models/Graph.h"

class ReliabilityManager {
private:
    Graph graph;
public:
    ReliabilityManager();

    vector<pair<std::string, double>> evaluateReservoirImpact(string code);

    Graph copyGraphWithoutVertex(string code);

    Graph copyGraphWithoutEdge(string orig, string dest);
};


#endif //DA_WATER_SUPPLY_RELIABILITYMANAGER_H
