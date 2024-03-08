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
    Reservoir(string name, DeliverySite *deliverySite, int id, string code, double maxDelivery);

    // Getters

    string getName() const;

    DeliverySite *getDeliverySite() const;


    double getMaxDelivery() const;

    // Setters

    void setName(const string &name);

    void setDeliverySite(DeliverySite *deliverySite);

    void setMaxDelivery(double maxDelivery);
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
