//
// Created by jpnsantos on 06/03/24.
//

#include "Reservoir.h"

Reservoir::Reservoir(std::string name, string municipality, int id, std::string code, double maxDelivery) {
    this->name = name;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->maxDelivery = maxDelivery;
}

string Reservoir::getName() const {
    return this->name;
}

string Reservoir::getMunicipality() const {
    return this->municipality;
}

double Reservoir::getMaxDelivery() const {
    return this->maxDelivery;
}

void Reservoir::setName(const std::string &name) {
    this->name = name;
}

void Reservoir::setMunicipality(std::string municipality) {
    this->municipality = municipality;
}

void Reservoir::setMaxDelivery(double maxDelivery) {
    this->maxDelivery = maxDelivery;
}