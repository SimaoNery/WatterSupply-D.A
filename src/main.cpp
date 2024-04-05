#include <iostream>
#include <fstream>
#include "utils/Dataset.h"
#include "managers/FlowManager.h"
#include "views/Menu.h"
#include "views/MainMenu.h"
#include "managers/ReliabilityManager.h"

using namespace std;

void clearOutputFile() {
    ofstream outputFile("output.txt", ios::trunc); // Open the file in truncation mode (clears existing content)
    if (outputFile.is_open()) {
        // File opened successfully, close it
        outputFile.close();
    }
}

int main() {
    clearOutputFile();
    cout << "Loading dataset..." << endl;
    Dataset *dataset = Dataset::getInstance();
    Menu *menu;
    // Point to main menu
    menu = new MainMenu();
    menu->display();
/*
    // test evaluation
    ReliabilityManager reliabilityManager;

    cout << "Evaluating reservoir impact..." << endl;
    for (auto p: dataset->getPipes()) {
        vector<pair<string, double>> res = reliabilityManager.evaluatePipeImpact(p.first, p.second);
        cout << "Pipe " << p.first << " - " << p.second << " impact: " << endl;
        for (auto city: res) {
            cout << "   - " << dataset->getNodeName(city.first) << " (" << city.first << "): " << city.second << endl;
        }
    }
*/
    /*  // test balance
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
      */
}
