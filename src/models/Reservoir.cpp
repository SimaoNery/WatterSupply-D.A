//
// Created by jpnsantos on 06/03/24.
//

#include "Reservoir.h"

Reservoir::Reservoir(std::string name, DeliverySite *deliverySite, int id, std::string code, double maxDelivery) {
    this->name = name;
    this->deliverySite = deliverySite;
    this->id = id;
    this->code = code;
    this->maxDelivery = maxDelivery;
}

string Reservoir::getName() const {
    return this->name;
}

DeliverySite *Reservoir::getDeliverySite() const {
    return this->deliverySite;
}

double Reservoir::getMaxDelivery() const {
    return this->maxDelivery;
}

void Reservoir::setName(const std::string &name) {
    this->name = name;
}

void Reservoir::setDeliverySite(DeliverySite *deliverySite) {
    this->deliverySite = deliverySite;
}

void Reservoir::setMaxDelivery(double maxDelivery) {
    this->maxDelivery = maxDelivery;
}