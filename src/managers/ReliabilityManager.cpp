//
// Created by jpnsantos on 21/03/24.
//

#include "ReliabilityManager.h"
#include "utils/Dataset.h"
#include "FlowManager.h"

ReliabilityManager::ReliabilityManager() {
    Dataset *dataset = Dataset::getInstance();
    this->graph = dataset->getGraph();
}

vector<pair<string, double>> ReliabilityManager::evaluateReservoirImpact(string reservoir) {
    vector<pair<string, double>> res;
    FlowManager originalFlowManager(graph);
    double flow1 = originalFlowManager.getMaxFlow();

    // Create a new graph that is a copy of the original graph but without the reservoir
    Graph g;
    for (Vertex *v: graph.getVertexSet()) {
        if (v->getCode() != reservoir) {
            g.addVertex(new Vertex(*v));
        }
    }
    for (Vertex *v: graph.getVertexSet()) {
        if (v->getCode() != reservoir) {
            Vertex *copiedVertex = g.findVertex(v->getCode());
            for (Edge *e: v->getAdj()) {
                if (e->getDest()->getCode() != reservoir) {
                    Vertex *dest = g.findVertex(e->getDest()->getCode());
                    copiedVertex->addEdge(dest, e->getWeight());
                }
            }
        }
    }

    FlowManager flowManager(g);
    double flow2 = flowManager.getMaxFlow();
    cout << "Original flow: " << flow1 << endl;
    cout << "New flow: " << flow2 << endl;
    return res;
}