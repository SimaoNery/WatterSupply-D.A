#include "VertexEdge.h"

//-----------------------Vertex-----------------------------------

Vertex::Vertex() {
    this->code = "";
    this->nodeType = NodeType::NONE;
}

Vertex::Vertex(string code, NodeType nodeType) {
    this->code = code;
    this->nodeType = nodeType;
}

Vertex::Vertex(string code, NodeType nodeType, string name, double demand, double population) {
    this->code = code;
    this->nodeType = nodeType;
    this->name = name;
    this->demand = demand;
    this->population = population;
}

Vertex::Vertex(string code, NodeType nodeType, string name, string municipality, double maxDelivery) {
    this->code = code;
    this->nodeType = nodeType;
    this->name = name;
    this->municipality = municipality;
    this->maxDelivery = maxDelivery;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
Edge *Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Vertex::removeEdge(string code) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getCode() == code) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        } else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

std::vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

unsigned int Vertex::getIndegree() const {
    return this->indegree;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getCode() == code) {
            it = dest->incoming.erase(it);
        } else {
            it++;
        }
    }
    delete edge;
}

// Getters
string Vertex::getCode() const {
    return this->code;
}

NodeType Vertex::getType() const {
    return this->nodeType;
}

string Vertex::getName() const {
    return this->name;
}

double Vertex::getDemand() const {
    return this->demand;
}

double Vertex::getPopulation() const {
    return this->population;
}

string Vertex::getMunicipality() const {
    return this->municipality;
}

double Vertex::getMaxDelivery() const {
    return this->maxDelivery;
}

// Setters

void Vertex::setCode(const string &code) {
    this->code = code;
}

void Vertex::setName(const string &name) {
    this->name = name;
}

void Vertex::setDemand(double demand) {
    this->demand = demand;
}

void Vertex::setPopulation(double population) {
    this->population = population;
}

void Vertex::setMunicipality(const string &municipality) {
    this->municipality = municipality;
}

void Vertex::setMaxDelivery(double maxDelivery) {
    this->maxDelivery = maxDelivery;
}

void Vertex::setType(NodeType type) {
    this->nodeType = type;
}



//-----------------------Edge-----------------------------------

Edge::Edge(Vertex *orig, Vertex *dest, double w) {
    this->orig = orig;
    this->dest = dest;
    this->weight = w;
}

Vertex *Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex *Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}

void Edge::setWeight(double d) {
    this->weight = d;
}
