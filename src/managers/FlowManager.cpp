#include "FlowManager.h"
#include "utils/Dataset.h"

#include <cmath>
#include <map>
#include <set>

FlowManager::FlowManager() {
    Dataset* dataset = Dataset::getInstance();
    this->g = dataset->getGraph();
}


// Function to test the given vertex 'w' and visit it if conditions are met
void FlowManager::testAndVisit(queue<Vertex*>& q, Edge* e, Vertex* w, double residual) {
    // Check if the vertex 'w' is not visited and there is residual capacity
    if (!w->isVisited() && residual > 0) {
        // Mark 'w' as visited, set the path through which it was reached, and enqueue it
        w->setVisited(true);
        w->setPath(e);
        q.push(w);
    }
}

// Function to find an augmenting path using Breadth-First Search
bool FlowManager::findAugmentingPath(Vertex* s, Vertex* t) {
    // Mark all vertices as not visited
    for (auto v : g.getVertexSet()) {
        v->setVisited(false);
    }
    // Mark the source vertex as visited and enqueue it
    s->setVisited(true);
    std::queue<Vertex*> q;
    q.push(s);

    // BFS to find an augmenting path
    while (!q.empty() && !t->isVisited()) {
        auto v = q.front();
        q.pop();
        // Process outgoing edges
        for (auto e : v->getAdj()) {
            testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
        }
        // Process incoming edges
        for (auto e : v->getIncoming()) {
            testAndVisit(q, e, e->getOrig(), e->getFlow());
        }
    }
    // Return true if a path to the target is found, false otherwise
    return t->isVisited();
}

// Function to find the minimum residual capacity along the augmenting path
double FlowManager::findMinResidualAlongPath(Vertex* s, Vertex* t) {
    double f = INF;
    // Traverse the augmenting path to find the minimum residual capacity
    for (auto v = t; v != s;) {
        auto e = v->getPath();
        if (e->getDest() == v) {
            f = std::min(f, e->getWeight() - e->getFlow());
            v = e->getOrig();
        }
        else {
            f = std::min(f, e->getFlow());
            v = e->getDest();
        }
    }
    // Return the minimum residual capacity
    return f;
}

// Function to augment flow along the augmenting path with the given flow value
void FlowManager::augmentFlowAlongPath(Vertex* s, Vertex* t, double f) {
    // Traverse the augmenting path and update the flow values accordingly
    for (auto v = t; v != s;) {
        cout << v->getCode() << " ";
        auto e = v->getPath();
        double flow = e->getFlow();
        if (e->getDest() == v) {
            e->setFlow(flow + f);
            v = e->getOrig();
        }
        else {
            e->setFlow(flow - f);
            v = e->getDest();
        }
    }
    cout << s->getCode() << endl;
}

// Main function implementing the Edmonds-Karp algorithm
void FlowManager::edmondsKarp(string source, string target) {
    // Find source and target vertices in the graph
    Vertex* s = g.findVertex(source);
    Vertex* t = g.findVertex(target);
    // Validate source and target vertices
    if (s == nullptr || t == nullptr || s == t)
        throw std::logic_error("Invalid source and/or target vertex");
    // Initialize flow on all edges to 0
    for (auto v : g.getVertexSet()) {
        for (auto e : v->getAdj()) {
            e->setFlow(0);
        }
    }
    // While there is an augmenting path, augment the flow along the path
    while (findAugmentingPath(s, t)) {
        double f = findMinResidualAlongPath(s, t);
        augmentFlowAlongPath(s, t, f);
    }
}

double FlowManager::getMaxFlow(string sink) {
    getMaxFlow();
    double max_flow = 0;
    auto v = g.findVertex(sink);

    for (auto edge : v->getIncoming()) {
        max_flow += edge->getFlow();
    }

    return max_flow;
}

double FlowManager::getMaxFlow() {
    double flow = 0;

    auto superSource = new Vertex("super_source", NodeType::RESERVOIR);
    auto superSink = new Vertex("super_sink", NodeType::DELIVERY_SITE);

    g.addVertex(superSource);
    g.addVertex(superSink);

    for (auto vert : g.getVertexSet()) {
        if (vert->getType() == NodeType::RESERVOIR) {
            superSource->addEdge(vert, vert->getMaxDelivery());
        }
    }

    for (auto vert : g.getVertexSet()) {
        if (vert->getType() == NodeType::DELIVERY_SITE) {
            vert->addEdge(superSink, vert->getDemand());
        }
    }

    edmondsKarp("super_source", "super_sink");

    for (auto edge : superSink->getIncoming()) {
        flow += edge->getFlow();
    }

    g.removeVertex("super_source");
    g.removeVertex("super_sink");
    return flow;
}

bool FlowManager::meetNeeds(string ds, double& difference) {
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

vector<pair<string, double>> FlowManager::getWaterNeeds() {
    vector<pair<string, double>> fails;
    double difference = 0;

    for (auto v : g.getVertexSet()) {
        if ((v->getType() == NodeType::DELIVERY_SITE) && !meetNeeds(v->getCode(), difference)) {
            fails.emplace_back(v->getCode(), difference);
        }
    }

    return fails;
}

CityMetrics FlowManager::getCityMetrics(string city) {
    getMaxFlow();
    double flow = 0;
    auto v = g.findVertex(city);

    for (auto edge : v->getIncoming()) {
        flow += edge->getFlow();
    }

    return { v->getCode(), flow, v->getDemand(), v->getDemand() - flow };
}

Metrics FlowManager::calculateMetrics() {
    double sum = 0;
    double max = 0;
    double variance = 0;
    int count = 0;

    for (auto v : g.getVertexSet()) {
        for (auto& edge : v->getAdj()) {
            sum += edge->getFlow() / edge->getWeight();
            max = std::max(max, edge->getFlow() / edge->getWeight());
            count++;
        }
    }

    double avg = sum / count;

    for (auto v : g.getVertexSet()) {
        for (auto& edge : v->getAdj()) {
            variance += pow(edge->getFlow() / edge->getWeight() - avg, 2) / (count - 1);
        }
    }

    return { avg, variance / count, max };
}

Metrics FlowManager::balanceLoad() {
    auto superSource = new Vertex("super_source", NodeType::RESERVOIR);
    auto superSink = new Vertex("super_sink", NodeType::DELIVERY_SITE);

    g.addVertex(superSource);
    g.addVertex(superSink);

    for (auto vert : g.getVertexSet()) {
        if (vert->getType() == NodeType::RESERVOIR) {
            superSource->addEdge(vert, vert->getMaxDelivery());
        }
    }

    for (auto vert : g.getVertexSet()) {
        if (vert->getType() == NodeType::DELIVERY_SITE) {
            vert->addEdge(superSink, vert->getDemand());
        }
    }

    for (auto& v : g.getVertexSet()) {
        v->setDist(INF);
        v->setPath(nullptr);
    }

    for (int i = 0; i < 100; i++) {
        superSource->setDist(0);
        superSource->setPath(nullptr);

        string sscode = superSource->getCode();
        set<pair<double, string>> pq;
        pq.emplace(0, sscode);

        Vertex* dest;

        // path that is kinda full
        while (!pq.empty()) {
            auto [cost, code] = *pq.begin();
            pq.erase(pq.begin());

            Vertex* u = g.findVertex(code);

            if (u->getType() == NodeType::DELIVERY_SITE) {
                dest = u;
                break;
            }

            for (auto edge : u->getAdj()) {
                auto w = edge->getDest();
                auto edge_cost = 1 - edge->getFlow() / edge->getWeight();

                if (w->getDist() > u->getDist() + edge_cost) {
                    w->setDist(u->getDist() + edge_cost);
                    w->setPath(edge);
                    pq.emplace(w->getDist(), w->getCode());
                }
            }
        }

        augmentFlowAlongPath(superSource, dest, -10);

        // find another path from dest to super source that is kinda empty 
        for (auto& v : g.getVertexSet()) {
            v->setDist(INF);
            v->setPath(nullptr);
        }
        superSource->setDist(0);

        pq.clear();
        pq.emplace(0, superSource->getCode());

        while (!pq.empty()) {
            auto [cost, code] = *pq.begin();
            pq.erase(pq.begin());

            Vertex* u = g.findVertex(code);

            if (u->getCode() == dest->getCode()) {
                break;
            }

            for (auto edge : u->getAdj()) {
                auto w = edge->getDest();
                // if (w->getCode() != dest->getCode() && w->getPath()) continue; // not repeat edges

                auto edge_cost = edge->getFlow() / edge->getWeight();

                if (w->getDist() > u->getDist() + edge_cost) {
                    w->setDist(u->getDist() + edge_cost);
                    w->setPath(edge);
                    pq.emplace(w->getDist(), w->getCode());
                }
            }

            // for (auto edge : u->getIncoming()) {
            //     auto w = edge->getOrig();

            //     // not repeat edges
            //     if (w == u->getPath()->getOrig()) continue;

            //     auto edge_cost = edge->getFlow() / edge->getWeight();

            //     if (w->getDist() > u->getDist() + edge_cost) {
            //         w->setDist(u->getDist() + edge_cost);
            //         w->setPath(edge);
            //         pq.emplace(w->getDist(), w->getCode());
            //     }
            // }
        }

        augmentFlowAlongPath(superSource, dest, 10);
    }

    g.removeVertex("super_source");
    g.removeVertex("super_sink");

    return calculateMetrics();
}