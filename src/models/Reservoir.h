//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_RESERVOIR_H
#define DA_WATER_SUPPLY_RESERVOIR_H

#include <iostream>
#include <string>
#include "DeliverySite.h"
#include "Node.h"

using namespace std;

class Reservoir : public Node {
private:
    string name;
    DeliverySite *deliverySite;
    double maxDelivery;
public:
    Reservoir() = default;

    // Getters

    string getName() const {
        return name;
    }


    DeliverySite *getDeliverySite() const {
        return deliverySite;
    }


    double getMaxDelivery() const {
        return maxDelivery;
    }

    // Setters

    void setName(const string &name) {
        Reservoir::name = name;
    }

    void setDeliverySite(DeliverySite *deliverySite) {
        Reservoir::deliverySite = deliverySite;
    }

    void setMaxDelivery(double maxDelivery) {
        Reservoir::maxDelivery = maxDelivery;
    }
};

namespace std {
    template<>
    struct hash<Reservoir> {
        size_t operator()(const Reservoir &reservoir) const {
            return hash<int>()(reservoir.getId());
        }
    };
}

#endif //DA_WATER_SUPPLY_RESERVOIR_H
