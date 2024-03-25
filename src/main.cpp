#include <iostream>
#include "utils/Dataset.h"
#include "managers/FlowManager.h"
#include "views/Menu.h"
#include "views/MainMenu.h"
#include "managers/ReliabilityManager.h"

using namespace std;

int main() {
    cout << "Loading dataset..." << endl;
    Dataset *dataset = Dataset::getInstance();
    Menu *menu;
    // Point to main menu
    menu = new MainMenu();
    //menu->display();

    // test evaluation
    ReliabilityManager reliabilityManager;

    cout << "Evaluating reservoir impact..." << endl;
    for (auto r: dataset->getGraph().getReservoirs()) {
        vector<pair<string, double>> res = reliabilityManager.evaluateReservoirImpact(r->getCode());
        cout << "Reservoir " << r->getCode() << " impact: " << endl;
        for (auto city: res) {
            cout << "   - " << dataset->getCityName(city.first) << " (" << city.first << "): " << city.second << endl;
        }
    }

    // test balance
    FlowManager flowManager;
    // Before balancing load
    Metrics preBalanceMetrics = flowManager.calculateMetrics();
    std::cout << "Metrics before load balancing:\n";
    std::cout << "Average Difference: " << preBalanceMetrics.averageDifference << "\n";
    std::cout << "Variance: " << preBalanceMetrics.variance << "\n";
    std::cout << "Max Difference: " << preBalanceMetrics.maxDifference << "\n";

// Balance the load
    Metrics postBalanceMetrics = flowManager.balanceLoad();

// After balancing load
    std::cout << "Metrics after load balancing:\n";
    std::cout << "Average Difference: " << postBalanceMetrics.averageDifference << "\n";
    std::cout << "Variance: " << postBalanceMetrics.variance << "\n";
    std::cout << "Max Difference: " << postBalanceMetrics.maxDifference << "\n";
}
