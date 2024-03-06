//
// Created by jpnsantos on 06/03/24.
//

#include <fstream>
#include <sstream>
#include "Dataset.h"

string CITIES_PATH = "data/Cities_Madeira.csv";
string PIPES_PATH = "data/Pipes_Madeira.csv";
string RESERVOIRS_PATH = "data/Reservoirs_Madeira.csv";
string STATIONS_PATH = "data/Stations_Madeira.csv";

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

void Dataset::loadStations() {

    ifstream file(STATIONS_PATH);
    if (!file.is_open()) {
        cout << "Error: File " << STATIONS_PATH << " not opened." << endl;
        return;
    }

    string row, stationCode, stationId, temp;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, stationId, ',');
        getline(line, stationCode, ',');
        getline(line, temp, ',');

        if (stationId.empty() || stationCode.empty()) {
            continue;
        }

        Station station(stoi(stationId), stationCode);
        //graph.addVertex(station);
        this->stations.insert(station);
    }
    file.close();

}

void Dataset::loadDeliverySites() {

}

void Dataset::loadReservoirs() {

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

