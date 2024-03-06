//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_DELIVERYSITE_H
#define DA_WATER_SUPPLY_DELIVERYSITE_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class DeliverySite : public Node {
private:
    string name;
    double demand;
    int population;
public:
    DeliverySite() = default;

    // Getters

    const string &getName() const {
        return name;
    }

    double getDemand() const {
        return demand;
    }

    int getPopulation() const {
        return population;
    }

    // Setters

    void setName(const string &name) {
        DeliverySite::name = name;
    }


    void setDemand(double demand) {
        DeliverySite::demand = demand;
    }

    void setPopulation(int population) {
        DeliverySite::population = population;
    }
};

namespace std {
    template<>
    struct hash<DeliverySite> {
        size_t operator()(const DeliverySite &ds) const {
            return hash<string>()(ds.getCode());
        }
    };
}

#endif //DA_WATER_SUPPLY_DELIVERYSITE_H
