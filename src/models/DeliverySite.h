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
    int id;
    string name;
    string code;
    double demand;
    int population;
public:
    DeliverySite() = default;

    // Getters
    int getId() const {
        return id;
    }

    const string &getName() const {
        return name;
    }

    const string &getCode() const {
        return code;
    }

    double getDemand() const {
        return demand;
    }

    int getPopulation() const {
        return population;
    }

    // Setters

    void setId(int id) {
        DeliverySite::id = id;
    }

    void setName(const string &name) {
        DeliverySite::name = name;
    }

    void setCode(const string &code) {
        DeliverySite::code = code;
    }

    void setDemand(double demand) {
        DeliverySite::demand = demand;
    }

    void setPopulation(int population) {
        DeliverySite::population = population;
    }

    bool operator==(const DeliverySite &ds) const {
        return id == ds.id;
    }

    bool operator<(const DeliverySite &ds) const {
        return id < ds.id;
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
