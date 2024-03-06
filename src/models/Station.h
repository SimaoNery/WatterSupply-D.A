//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_STATION_H
#define DA_WATER_SUPPLY_STATION_H

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

class Station : public Node {
public:
    Station(int id, string code);
};

namespace std {
    template<>
    struct hash<Station> {
        size_t operator()(const Station &station) const {
            return hash<int>()(station.getId());
        }
    };
}

#endif //DA_WATER_SUPPLY_STATION_H
