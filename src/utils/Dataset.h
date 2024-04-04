#ifndef DA_WATER_SUPPLY_DATASET_H
#define DA_WATER_SUPPLY_DATASET_H

#include "models/Graph.h"

// Pipe type alias
using Pipe = pair<string, string>;

class Dataset {
private:
    // Singleton instance
    static Dataset *dataset;

    // Graph instance
    Graph graph;

    // Pipes
    vector<Pipe> pipes;

    // Stations
    vector<pair<int, string>> stations;

    // Changes in the pipes (for Reliability tests)
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

    vector<pair<string, string>> getPipes();

    // Changes in the pipes
    void resetChanges();

    void addChange(Pipe pipe, double change);
};


#endif //DA_WATER_SUPPLY_DATASET_H
