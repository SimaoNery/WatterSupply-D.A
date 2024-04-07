#include "Graph.h"
#include <map>

int Graph::getNumVertex() const {
    return vertexSet.size();
}

vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex *Graph::findVertex(string code) const {
    for (auto v: vertexSet)
        if (v->getCode() == code)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */
int Graph::findVertexIdx(string code) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getCode() == code)
            return i;
    return -1;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(Vertex *v) {
    if (findVertex(v->getCode()) != nullptr)
        return false;
    vertexSet.push_back(v);
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
bool Graph::removeVertex(string code) {

    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getCode() == code) {

            auto v = *it;
            v->removeOutgoingEdges();

            for (auto u: vertexSet) {
                u->removeEdge(v->getCode());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(string source, string dest, double w) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);

    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (source) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(string source, string dest) const {
    Vertex *srcVertex = findVertex(source);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

bool Graph::addBidirectionalEdge(string source, string dest, double w) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */
vector<string> Graph::dfs() const {
    vector<string> res;
    for (auto v: vertexSet)
        v->setVisited(false);
    for (auto v: vertexSet)
        if (!v->isVisited())
            dfsVisit(v, res);
    return res;
}

/*
 * Performs a depth-first search (dfs) in a graph (this) from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */
vector<string> Graph::dfs(string source) const {
    vector<string> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    // Set that no vertex has been visited yet
    for (auto v: vertexSet) {
        v->setVisited(false);
    }
    // Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
void Graph::dfsVisit(Vertex *v, vector<string> &res) const {
    v->setVisited(true);
    res.push_back(v->getCode());
    for (auto &e: v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
vector<string> Graph::bfs(string source) const {
    vector<string> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v: vertexSet) {
        v->setVisited(false);
    }

    // Perform the actual BFS using a queue
    queue<Vertex *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getCode());
        for (auto &e: v->getAdj()) {
            auto w = e->getDest();
            if (!w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

bool Graph::isDAG() const {
    for (auto v: vertexSet) {
        v->setVisited(false);
        v->setProcessing(false);
    }
    for (auto v: vertexSet) {
        if (!v->isVisited()) {
            if (!dfsIsDAG(v)) return false;
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
bool Graph::dfsIsDAG(Vertex *v) const {
    v->setVisited(true);
    v->setProcessing(true);
    for (auto e: v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (!w->isVisited()) {
            if (!dfsIsDAG(w)) return false;
        }
    }
    v->setProcessing(false);
    return true;
}

/****************** toposort ********************/
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */
vector<string> Graph::topsort() const {
    vector<string> res;

    for (auto v: vertexSet) {
        v->setIndegree(0);
    }
    for (auto v: vertexSet) {
        for (auto e: v->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    queue<Vertex *> q;
    for (auto v: vertexSet) {
        if (v->getIndegree() == 0) {
            q.push(v);
        }
    }

    while (!q.empty()) {
        Vertex *v = q.front();
        q.pop();
        res.push_back(v->getCode());
        for (auto e: v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if (w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if (res.size() != vertexSet.size()) {
        //cout << "Impossible topological ordering!" << endl;
        res.clear();
        return res;
    }

    return res;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete[] m[i];
        delete[] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

/*
 * Gets the delivery sites from the dataset.
 * Complexity: O(n)
 * @return A vector with the delivery sites.
 */
vector<Vertex *> Graph::getDeliverySites() const {
    vector<Vertex *> res;
    for (auto v: vertexSet) {
        if (v->getType() == NodeType::DELIVERY_SITE) {
            res.push_back(v);
        }
    }
    return res;
}

/*
 * Gets the reservoirs from the dataset.
 * Complexity: O(n)
 * @return A vector with the reservoirs.
 */
vector<Vertex *> Graph::getReservoirs() const {
    vector<Vertex *> res;
    for (auto v: vertexSet) {
        if (v->getType() == NodeType::RESERVOIR) {
            res.push_back(v);
        }
    }
    return res;
}

/*
 * Gets the stations from the dataset.
 * Complexity: O(1)
 * @return A vector with the stations.
 */
vector<Vertex *> Graph::getStations() const {
    vector<Vertex *> res;
    for (auto v: vertexSet) {
        if (v->getType() == NodeType::STATION) {
            res.push_back(v);
        }
    }
    return res;
}
