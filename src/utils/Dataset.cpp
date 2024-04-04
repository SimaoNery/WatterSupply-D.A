//
// Created by jpnsantos on 06/03/24.
//

#include <fstream>
#include <sstream>
#include "Dataset.h"
#include "managers/FlowManager.h"

string CITIES_PATH = "data/small_data/Cities_Madeira.csv";
string PIPES_PATH = "data/small_data/Pipes_Madeira.csv";
string RESERVOIRS_PATH = "data/small_data/Reservoirs_Madeira.csv";
string STATIONS_PATH = "data/small_data/Stations_Madeira.csv";

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


        stations.emplace_back(stoi(stationId), stationCode);

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

        pipes.emplace_back(spA, spB);
    }

    file.close();
}

const Graph &Dataset::getGraph() const {
    return this->graph;
}

string Dataset::getNodeName(string code) {
    return graph.findVertex(code)->getName();
}

string Dataset::getReservoirName(string code) {
    return graph.findVertex(code)->getName();
}

vector<pair<string, string>> Dataset::getPipes() {
    return this->pipes;
}

void Dataset::resetChanges() {
    for (const auto &change: changes) {
        auto v = graph.findVertex(change.first.first);

        for (auto e: v->getAdj()) {
            if (e->getDest()->getCode() == change.first.second) {
                e->setWeight(change.second);
            }
        }
    }
    FlowManager flowManager;
    flowManager.getMaxFlow();
    changes.clear();
}

void Dataset::addChange(Pipe pipe, double capacity) {
    changes.emplace_back(pipe, capacity);
}
