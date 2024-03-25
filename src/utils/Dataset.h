//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_DATASET_H
#define DA_WATER_SUPPLY_DATASET_H

#include "models/Graph.h"

class Dataset {
private:
    static Dataset *dataset;

    Graph graph;

    vector<pair<string, string>> pipes;

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

    string getCityName(string code);

    vector<pair<string, string>> getPipes();
};


#endif //DA_WATER_SUPPLY_DATASET_H
