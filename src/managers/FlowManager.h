#ifndef DA_WATER_SUPPLY_FLOWMANAGER_H
#define DA_WATER_SUPPLY_FLOWMANAGER_H

#include "../models/Graph.h"

// Struct to store the metrics of a city
struct CityMetrics {
    string city;
    double incomingFlow;
    double difference;
};

// Struct to store the metrics of the flow
struct Metrics {
    double averageDifference;
    double variance;
    double maxDifference;
};

class FlowManager {
private:
    Graph g;

    void edmondsKarp(string source, string target);

    void augmentFlowAlongPath(Vertex* s, Vertex* t, double f);

    double findMinResidualAlongPath(Vertex* s, Vertex* t);

    bool findAugmentingPath(Vertex* s, Vertex* t);

    void testAndVisit(queue<Vertex*>& q, Edge* e, Vertex* w, double residual);

public:
    FlowManager();

    double getMaxFlow(string sink);

    double getMaxFlow();

    bool meetNeeds(string ds, double& difference);

    vector<pair<string, double>> getWaterNeeds();

    CityMetrics getCityMetrics(string city);

    Metrics calculateMetrics();

    Metrics balanceLoad();
};


#endif //DA_WATER_SUPPLY_FLOWMANAGER_H
