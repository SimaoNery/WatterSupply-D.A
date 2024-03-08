//
// Created by jpnsantos on 06/03/24.
//

#ifndef DA_WATER_SUPPLY_NODE_H
#define DA_WATER_SUPPLY_NODE_H

#include <iostream>
#include <string>

using namespace std;

class Node {
protected:
    int id;
    string code;
public:
    Node() = default;
    virtual ~Node() = default;

    Node(int id, string code);

    // Getters
    int getId() const;

    const string &getCode() const;

    // Setters
    void setId(int id);

    void setCode(const string &code);

    bool operator==(const Node &rhs) const {
        return id == rhs.id && code == rhs.code;
    }

    bool operator<(const Node &rhs) const {
        return id < rhs.id;
    }
};

namespace std {
    template<>
    struct hash<Node> {
        size_t operator()(const Node &node) const {
            return hash<int>()(node.getId()) ^ hash<string>()(node.getCode());
        }
    };
}

#endif //DA_WATER_SUPPLY_NODE_H
