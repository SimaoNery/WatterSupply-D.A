//
// Created by jpnsantos on 06/03/24.
//

#include "DeliverySite.h"

DeliverySite::DeliverySite(std::string city, int id, std::string code, double demand, double population) {
    this->name = city;
    this->id = id;
    this->code = code;
    this->demand = demand;
    this->population = population;
}

const string &DeliverySite::getName() const {
    return this->name;
}

double DeliverySite::getDemand() const {
    return this->demand;
}

double DeliverySite::getPopulation() const {
    return this->population;
}

void DeliverySite::setName(const std::string &name) {
    this->name = name;
}

void DeliverySite::setDemand(double demand) {
    this->demand = demand;
}

void DeliverySite::setPopulation(double population) {
    this->population = population;
}