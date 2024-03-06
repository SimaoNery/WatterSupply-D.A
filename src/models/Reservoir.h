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
    int id;
    DeliverySite *deliverySite;
    string code;
    double maxDelivery;
public:
    Reservoir() = default;

    // Getters
    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    DeliverySite *getDeliverySite() const {
        return deliverySite;
    }

    string getCode() const {
        return code;
    }

    double getMaxDelivery() const {
        return maxDelivery;
    }

    // Setters

    void setName(const string &name) {
        Reservoir::name = name;
    }

    void setId(int id) {
        Reservoir::id = id;
    }

    void setDeliverySite(DeliverySite *deliverySite) {
        Reservoir::deliverySite = deliverySite;
    }

    void setCode(const string code) {
        Reservoir::code = code;
    }

    void setMaxDelivery(double maxDelivery) {
        Reservoir::maxDelivery = maxDelivery;
    }

    bool operator==(const Reservoir &rhs) const {
        return name == rhs.name &&
               id == rhs.id &&
               *deliverySite == *rhs.deliverySite &&
               code == rhs.code &&
               maxDelivery == rhs.maxDelivery;
    }

    bool operator<(const Reservoir &rhs) const {
        return id < rhs.id;
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
