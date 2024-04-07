#include "FlowManager.h"
#include "utils/Dataset.h"

#include <cmath>
#include <map>

/**
 * @brief Constructs a new FlowManager object.
 *
 * The constructor initializes the FlowManager by retrieving an instance of the Dataset singleton and getting the graph from it.
 */
FlowManager::FlowManager() {
    Dataset *dataset = Dataset::getInstance();
    this->g = dataset->getGraph();
}


/**
 * @brief Function to find an augmenting path using Breadth-First Search
 *
 * @param s The source vertex of the path
 * @param t The target vertex of the path
 * @return true If an augmenting path is found, false otherwise
 */
void FlowManager::testAndVisit(queue<Vertex *> &q, Edge *e, Vertex *w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (!w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

/**
 * @brief Function to find an augmenting path using Breadth-First Search
 *
 * @param s The source vertex of the path
 * @param t The target vertex of the path
 * Complexity O(V + E)
 * @return true If an augmenting path is found, false otherwise
 */
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

/**
 * @brief Function to find the minimum residual capacity along an augmenting path
 *
 * @param s The source vertex of the path
 * @param t The target vertex of the path
 * Complexity O(V)
 * @return double The minimum residual capacity along the path
 */
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

/**
 * @brief Function to augment the flow along an augmenting path
 *
 * @param s The source vertex of the path
 * @param t The target vertex of the path
 * @param f The flow to augment
 * Complexity O(V)
 */
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

/**
 * @brief Function to calculate the maximum flow from a source to a target vertex
 *
 * @param source The source vertex code
 * @param target The target vertex code
 * Complexity O(V * E^2)
 */
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

/**
 * @brief Function to calculate the maximum flow from a source to a target vertex
 *
 * @param sink The target vertex code
 * @return double The maximum flow to the target vertex
 * Complexity O(V + E)
 */
double FlowManager::getMaxFlow(string sink) {
    getMaxFlow();
    double max_flow = 0;
    auto v = g.findVertex(sink);

    for (auto edge: v->getIncoming()) {
        max_flow += edge->getFlow();
    }

    return max_flow;
}

/**
 * @brief Function to calculate the maximum flow from a source to a target vertex
 * Complexity O(V + E)
 * @return double The maximum flow to the target vertex
 */
double FlowManager::getMaxFlow() {
    double flow = 0;

    auto superSource = new Vertex("super_source", NodeType::RESERVOIR);
    auto superSink = new Vertex("super_sink", NodeType::DELIVERY_SITE);

    g.addVertex(superSource);
    g.addVertex(superSink);

    for (auto vert: g.getVertexSet()) {
        if (vert->getType() == NodeType::RESERVOIR) {
            superSource->addEdge(vert, vert->getMaxDelivery());
        }
    }

    for (auto vert: g.getVertexSet()) {
        if (vert->getType() == NodeType::DELIVERY_SITE) {
            vert->addEdge(superSink, vert->getDemand());
        }
    }

    edmondsKarp("super_source", "super_sink");

    for (auto edge: superSink->getIncoming()) {
        flow += edge->getFlow();
    }

    g.removeVertex("super_source");
    g.removeVertex("super_sink");
    return flow;
}

/**
 * @brief Function to check if the water needs of a delivery site are met
 *
 * @param ds The delivery site code
 * @param difference The difference between the demand and the incoming flow
 * Complexity O(V + E)
 * @return bool True if the needs are met, false otherwise
 */
bool FlowManager::meetNeeds(string ds, double &difference) {
    getMaxFlow();
    auto v = g.findVertex(ds);
    double current = 0;

    CityMetrics cm = getCityMetrics(ds);

    if (cm.difference > 0) {
        difference = cm.difference;
        return false;
    }

    return true;
}

/**
 * @brief Function to get the water needs of all delivery sites
 * Complexity O(V + E)
 * @return vector<pair<string, double>> A vector containing the delivery site code and the difference between the demand and the incoming flow
 */
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

/**
 * @brief Function to get the metrics of a city
 * @param city The city code
 * Complexity O(V + E)
 * @return CityMetrics The metrics of the city
 */
CityMetrics FlowManager::getCityMetrics(string city) {
    getMaxFlow();
    double flow = 0;
    auto v = g.findVertex(city);

    for (auto edge: v->getIncoming()) {
        flow += edge->getFlow();
    }

    return {v->getCode(), flow, v->getDemand(), v->getDemand() - flow};
}