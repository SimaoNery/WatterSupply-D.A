#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "utils/data_structures/MutablePriorityQueue.h"
#include "VertexEdge.h"

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();

    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(string code) const;

    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(Vertex *v);

    bool removeVertex(string code);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(string source, string dest, double w) const;

    bool removeEdge(string source, string dest) const;

    bool addBidirectionalEdge(string source, string dest, double w) const;

    int getNumVertex() const;

    // Getters

    vector<Vertex *> getVertexSet() const;

    vector<Vertex *> getDeliverySites() const;

    vector<Vertex *> getReservoirs() const;

    vector<Vertex *> getStations() const;

    vector<string> dfs() const;

    vector<string> dfs(string source) const;

    void dfsVisit(Vertex *v, vector<string> &res) const;

    vector<string> bfs(string source) const;

    bool isDAG() const;

    bool dfsIsDAG(Vertex *v) const;

    std::vector<string> topsort() const;

protected:
    vector<Vertex *> vertexSet;    // vertex set

    double **distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(string code) const;
};

void deleteMatrix(int **m, int n);

void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */