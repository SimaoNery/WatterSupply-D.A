#ifndef DA_WATER_SUPPLY_FLOWMANAGER_H
#define DA_WATER_SUPPLY_FLOWMANAGER_H

#include "../models/Graph.h"

class FlowManager {
private:
    Graph g;

    void edmondsKarp(string source, string target);

    void augmentFlowAlongPath(Vertex *s, Vertex *t, double f);

    double findMinResidualAlongPath(Vertex *s, Vertex *t);

    bool findAugmentingPath(Vertex *s, Vertex *t);

    void testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual);

public:
    FlowManager();

    double getMaxFlow(string source, string sink);

    double getMaxFlow(string sink);

    double getMaxFlow();
};


#endif //DA_WATER_SUPPLY_FLOWMANAGER_H
