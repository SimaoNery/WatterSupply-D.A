#ifndef DA_WATER_SUPPLY_VERTEX_H
#define DA_WATER_SUPPLY_VERTEX_H

#include "Edge.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <optional>
#include "utils/data_structures/MutablePriorityQueue.h"


using namespace std;

enum class NodeType {
    NONE,
    RESERVOIR,
    STATION,
    DELIVERY_SITE
};

class Vertex {
public:
    // Constructor for a default Vertex
    Vertex();

    // Constructor for a Vertex of type STATION
    Vertex(string code, NodeType nodeType);

    // Constructor for a Vertex of type DELIVERY_SITE
    Vertex(string code, NodeType nodeType, string name, double demand, double population);

    // Constructor for a Vertex of type RESERVOIR
    Vertex(string code, NodeType nodeType, string name, string municipality, double maxDelivery);


    // Getters
    string getCode() const;

    NodeType getType() const;

    optional<string> getName() const;

    optional<double> getDemand() const;

    optional<double> getPopulation() const;

    optional<string> getMunicipality() const;

    optional<double> getMaxDelivery() const;

    // Setters

    void setCode(const string &code);

    void setName(const string &name);

    void setDemand(double demand);

    void setPopulation(double population);

    void setMunicipality(const string &municipality);

    void setMaxDelivery(double maxDelivery);

    void setType(NodeType type);


    bool operator<(Vertex &vertex) const; // required by MutablePriorityQueue

    vector<Edge *> getAdj() const;

    bool isVisited() const;

    bool isProcessing() const;

    unsigned int getIndegree() const;

    double getDist() const;

    Edge *getPath() const;

    vector<Edge *> getIncoming() const;

    void setVisited(bool visited);

    void setProcessing(bool processing);

    void setIndegree(unsigned int indegree);

    void setDist(double dist);

    void setPath(Edge *path);

    Edge *addEdge(Vertex *dest, double w);

    bool removeEdge(string code);

    void removeOutgoingEdges();

    friend class MutablePriorityQueue<Vertex>;

protected:           // info node
    string code; // unique string identifier
    NodeType nodeType; // type of node

    optional<string> name; // ds or reservoir
    optional<double> demand; // ds
    optional<double> population; // ds
    optional<string> municipality; // reservoir
    optional<double> maxDelivery; // reservoir


    vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree = 0; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    vector<Edge *> incoming; // incoming edges

    int queueIndex = 0;        // required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);


};


#endif //DA_WATER_SUPPLY_VERTEX_H
