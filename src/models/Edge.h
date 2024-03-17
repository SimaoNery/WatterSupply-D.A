//
// Created by jpnsantos on 16/03/24.
//

#ifndef DA_WATER_SUPPLY_EDGE_H
#define DA_WATER_SUPPLY_EDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "utils/data_structures/MutablePriorityQueue.h"
#include "Vertex.h"

class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex *getDest() const;

    double getWeight() const;

    bool isSelected() const;

    Vertex *getOrig() const;

    Edge *getReverse() const;

    double getFlow() const;

    void setSelected(bool selected);

    void setReverse(Edge *reverse);

    void setFlow(double flow);

protected:
    Vertex *dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow = 0; // for flow-related problems
};


#endif //DA_WATER_SUPPLY_EDGE_H
