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
    double population;
public:
    DeliverySite() = default;
    DeliverySite(string city, int id, string code, double demand, double population);

    // Getters

    const string &getName() const;

    double getDemand() const;

    double getPopulation() const;

    // Setters

    void setName(const string &name);

    void setDemand(double demand);

    void setPopulation(double population);
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
