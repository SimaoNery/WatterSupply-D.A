//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_DATASET_H
#define DA_WATER_SUPPLY_DATASET_H

#include "models/Graph.h"

using Pipe = pair<string, string>;

class Dataset {
private:
    static Dataset *dataset;

    Graph graph;

    vector<Pipe> pipes;

    vector<pair<Pipe, double>> changes;

    // Private constructor so that no objects can be created.
    Dataset();

    // Load data methods
    void loadDeliverySites();

    void loadReservoirs();

    void loadStations();

    void loadPipes();

public:
    // Static access method
    static Dataset *getInstance();

    // Delete copy constructor and assignment operator
    Dataset(const Dataset &) = delete;

    void operator=(const Dataset &) = delete;

    // Getters
    const Graph &getGraph() const;

    string getNodeName(string code);

    string getReservoirName(string code);

    vector<pair<int, string>> stations;

    vector<pair<string, string>> getPipes();

    void resetChanges();

    void addChange(Pipe pipe, double change);
};


#endif //DA_WATER_SUPPLY_DATASET_H
