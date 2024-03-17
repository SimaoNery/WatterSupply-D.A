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


        auto v = new Vertex(stationCode, NodeType::STATION);
        graph.addVertex(v);
    }

    file.close();
}

void Dataset::loadDeliverySites() {
    ifstream file(CITIES_PATH);
    if (!file.is_open()) {
        cout << "Error: File " << CITIES_PATH << " not opened." << endl;
        return;
    }

    string row, name, dsId, dsCode, demand, population;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, name, ',');
        getline(line, dsId, ',');
        getline(line, dsCode, ',');
        getline(line, demand, ',');
        getline(line, population, '\r');

        auto v = new Vertex(dsCode, NodeType::DELIVERY_SITE, name, stod(demand), stod(population));
        graph.addVertex(v);
    }

    file.close();
}

void Dataset::loadReservoirs() {
    ifstream file(RESERVOIRS_PATH);
    if (!file.is_open()) {
        cout << "Error: File " << RESERVOIRS_PATH << " not opened." << endl;
        return;
    }

    string row, res, municipality, resId, resCode, maxDelivery;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, res, ',');
        getline(line, municipality, ',');
        getline(line, resId, ',');
        getline(line, resCode, ',');
        getline(line, maxDelivery, '\r');


        auto v = new Vertex(resCode, NodeType::RESERVOIR, res, municipality, stod(maxDelivery));
        graph.addVertex(v);
    }

    file.close();
}


void Dataset::loadPipes() {
    ifstream file(PIPES_PATH);
    if (!file.is_open()) {
        cout << "Error: File " << PIPES_PATH << " not opened." << endl;
        return;
    }

    string row, spA, spB, capacity, direction;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, spA, ',');
        getline(line, spB, ',');
        getline(line, capacity, ',');
        getline(line, direction, '\r');

        int aux = stoi(direction);
        int weight = stoi(capacity);

        if (aux == 0) {
            graph.addBidirectionalEdge(spA, spB, weight);
        } else {
            graph.addEdge(spA, spB, weight);
        }

    }

    file.close();
}

const Graph &Dataset::getGraph() const {
    return this->graph;
}
