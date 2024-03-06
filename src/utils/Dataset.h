//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_DATASET_H
#define DA_WATER_SUPPLY_DATASET_H

#include <unordered_set>
#include "data_structures/Graph.h"
#include "../models/Node.h"
#include "../models/DeliverySite.h"
#include "../models/Reservoir.h"
#include "../models/Station.h"

class Dataset {
private:
    Graph<Node> graph;

    unordered_set<DeliverySite> deliverySites;
    unordered_set<Reservoir> reservoirs;
    unordered_set<Station> stations;

    static Dataset* dataset;
    // Private constructor so that no ovjects can be created.
    Dataset();

    // Load data methods
    void loadDeliverySites();
    void loadReservoirs();
    void loadStations();
    void loadPipes();

public:
    // Static access method
    static Dataset* getInstance();

    // Delete copy constructor and assignment operator
    Dataset(const Dataset&) = delete;
    void operator=(const Dataset&) = delete;

    // Getters
    const Graph<Node>& getGraph() const;
    const unordered_set<DeliverySite>& getDeliverySites() const;
    const unordered_set<Reservoir>& getReservoirs() const;
    const unordered_set<Station>& getStations() const;
};


#endif //DA_WATER_SUPPLY_DATASET_H
