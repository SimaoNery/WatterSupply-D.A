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
    int id;
    string code;
public:
    Station(int id, string code);

    // Getters
    int getId() const {
        return id;
    }

    const string getCode() const {
        return code;
    }

    // Setters

    void setId(int id) {
        Station::id = id;
    }

    void setCode(const string &code) {
        Station::code = code;
    }

    bool operator==(const Station &rhs) const {
        return id == rhs.id;
    }

    bool operator<(const Station &rhs) const {
        return id < rhs.id;
    }
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
