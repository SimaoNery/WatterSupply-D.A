#ifndef DA_WATER_SUPPLY_VERTEXEDGE_H
#define DA_WATER_SUPPLY_VERTEXEDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <optional>
#include "utils/data_structures/MutablePriorityQueue.h"


using namespace std;

//-----------------------Vertex-----------------------------------

enum class NodeType {
    NONE,
    RESERVOIR,
    STATION,
    DELIVERY_SITE
};

class Edge;

class Vertex {
private:           // info node
    string code; // unique string identifier
    NodeType nodeType; // type of node

    string name; // ds or reservoir
    double demand; // ds
    double population; // ds
    string municipality; // reservoir
    double maxDelivery; // reservoir


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

public:
    // Constructor for a default VertexEdge
    Vertex();

    // Constructor for a VertexEdge of type STATION
    Vertex(string code, NodeType nodeType);

    // Constructor for a VertexEdge of type DELIVERY_SITE
    Vertex(string code, NodeType nodeType, string name, double demand, double population);

    // Constructor for a VertexEdge of type RESERVOIR
    Vertex(string code, NodeType nodeType, string name, string municipality, double maxDelivery);


    // Getters
    string getCode() const;

    NodeType getType() const;

    string getName() const;

    double getDemand() const;

    double getPopulation() const;

    string getMunicipality() const;

    double getMaxDelivery() const;

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
};

//-----------------------Edge-----------------------------------
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




#endif //DA_WATER_SUPPLY_VERTEXEDGE_H
