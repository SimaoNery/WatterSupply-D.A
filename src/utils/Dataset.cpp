//
// Created by jpnsantos on 06/03/24.
//

#include "Dataset.h"

Dataset *Dataset::dataset = nullptr;

Dataset::Dataset() {
    loadStations();
    loadDeliverySites();
    loadReservoirs();
    loadPipes();
}

/**
 * @brief Gets the singleton instance of the Dataset class.
 * Complexity: O(1)
 * @return A pointer to the instance.
 */
Dataset *Dataset::getInstance() {
    if (dataset == nullptr) {
        dataset = new Dataset();
        return dataset;
    } else {
        return dataset;
    }
}


void Dataset::loadDeliverySites() {

}

void Dataset::loadReservoirs() {

}

void Dataset::loadStations() {
    Station station1 = Station(0, "teste");
    this->stations.insert(station1);
}

void Dataset::loadPipes() {

}

const Graph<Node> &Dataset::getGraph() const {
    return this->graph;
}

const unordered_set<DeliverySite> &Dataset::getDeliverySites() const {
    return this->deliverySites;
}

const unordered_set<Reservoir> &Dataset::getReservoirs() const {
    return this->reservoirs;
}

const unordered_set<Station> &Dataset::getStations() const {
    return this->stations;
}

