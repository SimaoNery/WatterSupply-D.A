//
// Created by jpnsantos on 06/03/24.
//

#include <fstream>
#include <sstream>
#include "Dataset.h"

string CITIES_PATH = "data/Cities.csv";
string PIPES_PATH = "data/Pipes.csv";
string RESERVOIRS_PATH = "data/Reservoir.csv";
string STATIONS_PATH = "data/Stations.csv";

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

    string row, stationCode, stationId;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, stationId, ',');
        getline(line, stationCode, '\r');

        Station station(stoi(stationId), stationCode);
        //graph.addVertex(station);
        this->stations.insert(station);
    }

    file.close();
}

void Dataset::loadDeliverySites() {
    ifstream file(CITIES_PATH);
    if (!file.is_open()) {
        cout << "Error: File " << CITIES_PATH << " not opened." << endl;
        return;
    }

    string row, city, dsId, dsCode, demand, population, temp;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, city, ',');
        getline(line, dsId, ',');
        getline(line, dsCode, ',');
        getline(line, demand, ',');
        getline(line, population, ',');
        getline(line, temp, '\r');


        DeliverySite deliverySite(city, stoi(dsId), dsCode, stod(demand), stod(population));
        //graph.addVertex(station);
        this->deliverySites.insert(deliverySite);
    }
    
    file.close();
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

