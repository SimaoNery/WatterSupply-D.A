#include "FlowManager.h"
#include "utils/Dataset.h"

FlowManager::FlowManager() {
    Dataset *dataset = Dataset::getInstance();
    this->g = dataset->getGraph();
}


// Function to test the given vertex 'w' and visit it if conditions are met
void FlowManager::testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (!w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
bool FlowManager::findAugmentingPath(Vertex *s, Vertex *t) {
// Mark all vertices as not visited
    for (auto v: g.getVertexSet()) {
        v->setVisited(false);
    }
// Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex *> q;
    q.push(s);
// BFS to find an augmenting path
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
// Process outgoing edges
        for (auto e: v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
// Process incoming edges
        for (auto e: v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
// Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
double FlowManager::findMinResidualAlongPath(Vertex *s, Vertex *t) {
    double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        } else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
// Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
void FlowManager::augmentFlowAlongPath(Vertex *s, Vertex *t, double f) {
// Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        } else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
}

// Main function implementing the Edmonds-Karp algorithm
void FlowManager::edmondsKarp(string source, string target) {
// Find source and target vertices in the graph
    Vertex *s = g.findVertex(source);
    Vertex *t = g.findVertex(target);
// Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
    for (auto v: g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            e->setFlow(0);
        }
    }
// While there is an augmenting path, augment the flow along the path
    while (findAugmentingPath(s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

double FlowManager::getMaxFlow(string source, string sink) {
    double flow = 0;
    edmondsKarp(source, sink);

    auto v = g.findVertex(sink);

    for (auto edge: v->getIncoming()) {
        flow += edge->getFlow();
    }

    return flow;
}

double FlowManager::getMaxFlow(string sink) {
    auto superSource = new Vertex("R_Super", NodeType::RESERVOIR);
    g.addVertex(superSource);

    for (auto vert: g.getVertexSet()) {
        if (vert->getType() == NodeType::RESERVOIR) {
            superSource->addEdge(vert, INF);
        }
    }

    double flow = getMaxFlow("R_Super", sink);

    g.removeVertex("R_Super");
    return flow;
}

double FlowManager::getMaxFlow() {
    auto superSink = new Vertex("C_Super", NodeType::DELIVERY_SITE);

    g.addVertex(superSink);

    for (auto vert: g.getVertexSet()) {
        if (vert->getType() == NodeType::DELIVERY_SITE) {
            vert->addEdge(superSink, INF);
        }
    }

    double flow = getMaxFlow("C_Super");

    g.removeVertex("C_Super");
    return flow;
}

bool FlowManager::meetNeeds(string ds, double &difference) {
    auto v = g.findVertex(ds);
    double current = 0;

    for (auto edge: v->getIncoming()) {
        current += edge->getWeight();
    }

    if (v->getDemand() > current) {
        difference = v->getDemand() - current;
        return false;
    }

    return true;
}

vector<pair<string, double>> FlowManager::getWaterNeeds() {
    vector<pair<string, double>> fails;
    double difference = 0;

    for (auto v: g.getVertexSet()) {
        if ((v->getType() == NodeType::DELIVERY_SITE) && !meetNeeds(v->getCode(), difference)) {
            fails.emplace_back(v->getCode(), difference);
        }
    }

    return fails;
}