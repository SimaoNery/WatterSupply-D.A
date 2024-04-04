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

/**
 * @brief Function to calculate the metrics of the flow
 * Complexity O(V + E)
 * @return Metrics The metrics of the flow
 */
Metrics FlowManager::calculateMetrics() {
    double averageDifference = 0;
    double variance = 0;
    double maxDifference = 0;
    int edgeCount = 0;
    // Calculate the total difference and the maximum difference
    double totalDifference = 0;
    for (auto v: g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            // Ignore edges with infinite capacity
            if (e->getWeight() == INF) continue;

            double difference = e->getWeight() - e->getFlow();
            totalDifference += difference;
            maxDifference = max(maxDifference, difference);
            edgeCount++;
        }
    }

    // Calculate the average difference
    averageDifference = totalDifference / edgeCount;

    // Calculate the variance
    double totalSquaredDifference = 0;
    for (auto v: g.getVertexSet()) {
        for (auto e: v->getAdj()) {
            // Ignore edges with infinite capacity

            double difference = e->getWeight() - e->getFlow();
            totalSquaredDifference += pow(difference - averageDifference, 2);
        }
    }
    variance = totalSquaredDifference / edgeCount;

    // Return the calculated metrics
    return {averageDifference, variance, maxDifference};
}

/**
 * @brief Function to balance the load of the flow
 * Complexity O(V + E)
 * @return Metrics The new metrics of the flow
 */
Metrics FlowManager::balanceLoad() {
    // Create a super source and a super sink
    auto *superSource = new Vertex("super_source", NodeType::RESERVOIR);
    auto *superSink = new Vertex("super_sink", NodeType::DELIVERY_SITE);

    // Add the super source and super sink to the graph
    g.addVertex(superSource);
    g.addVertex(superSink);

    // Connect the super source to all sources and all sinks to the super sink
    for (auto v: g.getVertexSet()) {
        if (v->getType() == NodeType::RESERVOIR) {
            superSource->addEdge(v, v->getMaxDelivery());
        }
        if (v->getType() == NodeType::DELIVERY_SITE) {
            v->addEdge(superSink, v->getDemand());
        }
    }

    // Calculate the initial metrics
    Metrics metrics = calculateMetrics();
    double averageDifference = metrics.averageDifference;
    double variance = metrics.variance;

    // Set a threshold for the variance
    double threshold = 0.01;

    // While the variance is above the threshold
    while (variance > threshold) {
        // Perform a DFS from the super source to the super sink
        bool isFlowChanged = dfs(superSource, INF);

        // If the DFS doesn't change the flow anymore, break the loop
        if (!isFlowChanged) break;

        // Recalculate the metrics
        metrics = calculateMetrics();
        averageDifference = metrics.averageDifference;
        variance = metrics.variance;
    }

    // Remove the super source and super sink from the graph
    g.removeVertex("super_source");
    g.removeVertex("super_sink");

    // Return the new metrics
    return metrics;
}

/**
 * @brief Function to perform a depth-first search (DFS) to balance the load of the flow
 *
 * @param v The current vertex
 * @param minFlow The minimum flow that can be pushed through the path
 * Complexity O(V + E)
 * @return bool True if the flow was changed, false otherwise
 */
bool FlowManager::dfs(Vertex *v, double minFlow) {
    // If the current vertex is the sink, return true
    if (v->getType() == NodeType::DELIVERY_SITE) return true;

    // Mark the current vertex as visited
    v->setVisited(true);

    // For each unvisited adjacent vertex, visit it and try to push flow to it
    for (auto e: v->getAdj()) {
        Vertex *w = e->getDest();
        if (!w->isVisited()) {
            double residual = e->getWeight() - e->getFlow(); // Calculate the residual capacity of the edge

            // Calculate the total outgoing flow of the vertex
            double totalOutgoingFlow = 0;
            for (auto edge: v->getAdj()) {
                totalOutgoingFlow += edge->getFlow();
            }

            // Check if the edge has enough residual capacity and the source can provide the new flow
            if (residual >= minFlow && totalOutgoingFlow >= minFlow) {
                // If you can push flow to the sink through the adjacent vertex, update the flow along the path
                double newFlow = min(residual, minFlow);
                e->setFlow(e->getFlow() + newFlow);

                // Recursively call dfs on the adjacent vertex
                if (dfs(w, newFlow)) return true;

                // If the dfs call returns false, undo the flow update
                e->setFlow(e->getFlow() - newFlow);
            }
        }
    }

    return false;
}