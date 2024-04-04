//
// Created by jpnsantos on 21/03/24.
//

#include "ReliabilityManager.h"
#include "utils/Dataset.h"
#include "FlowManager.h"

/**
 * @brief Constructor for the ReliabilityManager class.
 * Initializes the original metrics for each city.
 * Complexity: O(n)
 */
ReliabilityManager::ReliabilityManager() {
    Dataset *dataset = Dataset::getInstance();
    this->graph = dataset->getGraph();

    FlowManager flowManager;
    flowManager.getMaxFlow();

    for (auto city: graph.getDeliverySites()) {
        auto aux = flowManager.getCityMetrics(city->getCode());
        originalMetrics.push_back(aux);
    }
}

/**
 * @brief Gets the metrics for a city.
 * Complexity: O(n)
 * @param code The city code.
 * @return The metrics for the city.
 */
CityMetrics ReliabilityManager::getCityMetrics(std::string code) {
    CityMetrics res;

    for (const auto &metrics: originalMetrics) {
        if (metrics.city == code) {
            res = metrics;
        }
    }

    return res;
}

/**
 * @brief Evaluates the impact of removing a reservoir.
 * Complexity: O(n)
 * @param code The reservoir code.
 * @return A vector with the affected cities and the difference in flow.
 */
vector<pair<string, double>> ReliabilityManager::evaluateReservoirImpact(string code) {
    vector<pair<string, double>> res;
    Dataset *dataset = Dataset::getInstance();

    FlowManager flowManager;
    auto v = graph.findVertex(code);

    for (auto e: v->getAdj()) {
        dataset->addChange(make_pair(e->getOrig()->getCode(), e->getDest()->getCode()), e->getWeight());
        e->setWeight(0);
    }

    for (auto city: graph.getDeliverySites()) {
        CityMetrics changedMetrics = flowManager.getCityMetrics(city->getCode());

        // If the city has less flow in the copied graph, it's affected by the removal of the reservoir
        if (changedMetrics.incomingFlow < getCityMetrics(city->getCode()).incomingFlow) {
            res.emplace_back(city->getCode(), changedMetrics.difference);
        }
    }

    return res;
}

/**
 * @brief Evaluates the impact of removing a station.
 * Complexity: O(n)
 * @param code The station code.
 * @return A vector with the affected cities and the difference in flow.
 */
vector<pair<string, double>> ReliabilityManager::evaluateStationImpact(string code) {
    vector<pair<string, double>> res;
    Dataset *dataset = Dataset::getInstance();


    FlowManager flowManager;

    auto v = graph.findVertex(code);
    for (auto e: v->getAdj()) {
        dataset->addChange(make_pair(e->getOrig()->getCode(), e->getDest()->getCode()), e->getWeight());
        e->setWeight(0);
    }

    for (auto city: graph.getDeliverySites()) {
        CityMetrics changedMetrics = flowManager.getCityMetrics(city->getCode());

        // If the city has less flow in the copied graph, it's affected by the removal of the reservoir
        if (changedMetrics.incomingFlow < getCityMetrics(city->getCode()).incomingFlow) {
            res.emplace_back(city->getCode(), changedMetrics.difference);
        }
    }

    return res;
}

/**
 * @brief Evaluates the impact of removing a pipe.
 * Complexity: O(n)
 * @param source The source city code.
 * @param dest The destination city code.
 * @return A vector with the affected cities and the difference in flow.
 */
vector<pair<string, double>> ReliabilityManager::evaluatePipeImpact(string source, string dest) {
    vector<pair<string, double>> res;
    Dataset *dataset = Dataset::getInstance();

    FlowManager flowManager;

    auto v1 = graph.findVertex(source);
    auto v2 = graph.findVertex(dest);


    for (auto e: v1->getAdj()) {
        if (e->getDest()->getCode() == dest) {
            dataset->addChange(make_pair(e->getOrig()->getCode(), e->getDest()->getCode()), e->getWeight());
            e->setWeight(0);
        }
    }
    for (auto e: v2->getAdj()) {
        if (e->getDest()->getCode() == source) {
            dataset->addChange(make_pair(e->getOrig()->getCode(), e->getDest()->getCode()), e->getWeight());
            e->setWeight(0);
        }
    }

    for (auto city: graph.getDeliverySites()) {
        CityMetrics changedMetrics = flowManager.getCityMetrics(city->getCode());

        // If the city has less flow in the copied graph, it's affected by the removal of the reservoir
        if (changedMetrics.incomingFlow < getCityMetrics(city->getCode()).incomingFlow) {
            res.emplace_back(city->getCode(), changedMetrics.difference);
        }
    }

    return res;
}

/**
 * @brief Evaluates the impact of removing a pipe.
 * Complexity: O(n)
 * @param code The city code.
 * @return A vector with the affected pipes and the difference in flow.
 */
vector<pair<pair<string, string>, double>> ReliabilityManager::evaluateCityImpactByPipes(string code) {

    vector<pair<pair<string, string>, double>> res;

    FlowManager flowManager;
    Dataset *dataset = Dataset::getInstance();

    // calculate affecting pipes for each city
    for (const auto &pipe: dataset->getPipes()) {
        dataset->resetChanges();
        // Create a new graph that is a copy of the original graph but without the reservoir
        auto v1 = graph.findVertex(pipe.first);
        auto v2 = graph.findVertex(pipe.second);

        for (auto e: v1->getAdj()) {
            if (e->getDest()->getCode() == pipe.second) {
                dataset->addChange(make_pair(e->getOrig()->getCode(), e->getDest()->getCode()), e->getWeight());
                e->setWeight(0);
            }
        }
        for (auto e: v2->getAdj()) {
            if (e->getDest()->getCode() == pipe.first) {
                dataset->addChange(make_pair(e->getOrig()->getCode(), e->getDest()->getCode()), e->getWeight());
                e->setWeight(0);
            }
        }
        CityMetrics changedMetrics = flowManager.getCityMetrics(code);

        // If the city has less flow in the copied graph, it's affected by the removal of the reservoir
        if (changedMetrics.incomingFlow < getCityMetrics(code).incomingFlow) {
            res.emplace_back(make_pair(pipe.first, pipe.second),
                             changedMetrics.difference);
        }


    }

    return res;
}



