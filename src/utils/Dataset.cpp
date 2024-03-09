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
        graph.addVertex(station);
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

    string row, city, dsId, dsCode, demand, population;
    getline(file, row);

    while (getline(file, row)) {
        istringstream line(row);
        getline(line, city, ',');
        getline(line, dsId, ',');
        getline(line, dsCode, ',');
        getline(line, demand, ',');
        getline(line, population, '\r');


        DeliverySite deliverySite(city, stoi(dsId), dsCode, stod(demand), stod(population));
        graph.addVertex(deliverySite);
        this->deliverySites.insert(deliverySite);
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


        /*
        DeliverySite aux;
        for(const auto& city : deliverySites){
            if(city.getName() == municipality){
                aux = city;
            }
        }
        */

        Reservoir reservoir(res, municipality, stoi(resId), resCode, stod(maxDelivery));
        graph.addVertex(reservoir);
        this->reservoirs.insert(reservoir);
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

        Node v1;
        Node v2;

        for(auto vert : graph.getVertexSet()){
            if(vert->getInfo().getCode() == spA){
                v1 = vert->getInfo();
            }
            else if(vert->getInfo().getCode() == spB) {
                v2 = vert->getInfo();
            }
        }

        if(aux == 0){
            graph.addBidirectionalEdge(v1, v2, weight);
        }
        else{
            graph.addEdge(v1, v2, weight);
        }

    }

    file.close();
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

