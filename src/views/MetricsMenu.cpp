//
// Created by jpnsantos on 21/03/24.
//

#include <fstream>
#include "MetricsMenu.h"
#include "MainMenu.h"
#include "managers/FlowManager.h"

MetricsMenu::MetricsMenu() {
    flowManager = FlowManager();
}


/**
     * Displays the main menu for the statistics options.
     * Complexity: O(1), as the number of menu options is fixed.
     * @brief Displays the main menu and handles user input for the statistics options.
     * @see showNetworkFlow(), showFlowForCity(), showFlowForAllCities(), showWaterNeeds(), showBalanceFlow(), backToMain()
     * @return void
     */
void MetricsMenu::display() {
    system("clear");
    cout << "****************************************************************************************\n"
         << "*   basic service metrics                                                              *\n"
         << "*                                                                                      *\n"
         << "*     1) See network flow                                                              *\n"
         << "*     2) See flow for a specific city                                                  *\n"
         << "*     3) See flow for each city                                                        *\n"
         << "*                                                                                      *\n"
         << "*     4) See cities that cannot be supplied for their water needs                      *\n"
         << "*                                                                                      *\n"
         << "*     5) Balance Flow                                                                  *\n"
         << "*                                                                              0) Back *\n"
         << "****************************************************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || (option < 0 || option > 5)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch (option) {
        case 1:
            showNetworkFlow();
            break;
        case 2:
            showFlowForCity();
            break;
        case 3:
            showFlowForAllCities();
            break;
        case 4:
            showWaterNeeds();
            break;
        case 5:
            showBalanceFlow();
            break;
        case 0:
            backToMain();
            break;
    }
}

/**
 * @brief Navigates back to the main menu.
 */
void MetricsMenu::backToMain() {
    MainMenu mainMenu;
    mainMenu.display();
}

/**
 * @brief Displays the footer option and handles user input.
 */
void MetricsMenu::printFooterOption() {
    int option;
    cout << "\n                                                   0) Back   "
         << "\n***********************************************************\n"
         << "Option: ";
    while (!(cin >> option) || option != 0) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    this->display();
}

/**
 * @brief Displays the Network Flow
 */
void MetricsMenu::showNetworkFlow() {
    ofstream outputFile("output.txt", ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << "\n***********************************************************\n"
                   << "\nNetwork flow: " << flowManager.getMaxFlow() << " (m3/s) " << endl;
        outputFile.close(); // Close the file
    }

    cout << "\n***********************************************************\n"
         << "\nNetwork flow: " << flowManager.getMaxFlow() << " (m3/s) " << endl;
    printFooterOption();
}


/**
 * @brief Displays the flow for a specific city
 */
void MetricsMenu::showFlowForCity() {
    Dataset *dataset = Dataset::getInstance();
    string code;
    cout << "Enter city code: ";
    cin >> code;
    transform(code.begin(), code.end(), code.begin(), ::toupper);

    ofstream outputFile("output.txt", ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        outputFile << "\n***********************************************************\n";
        outputFile << "\nFlow getting into " << dataset->getNodeName(code) << " (" << code << ")" << ": "
                   << flowManager.getMaxFlow(code)
                   << " (m3/s) " << endl;
        outputFile.close(); // Close the file
    }

    cout << "\n***********************************************************\n";
    cout << "\nFlow getting into " << dataset->getNodeName(code) << " (" << code << ")" << ": "
         << flowManager.getMaxFlow(code)
         << " (m3/s) " << endl;
    printFooterOption();
}

/**
 * @brief Displays the flow all the cities
 */
void MetricsMenu::showFlowForAllCities() {
    ofstream outputFile("output.txt", ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        Dataset *dataset = Dataset::getInstance();
        outputFile << "\n***********************************************************\n";
        outputFile << "\n Flow getting to each city: \n";
        for (auto city: dataset->getGraph().getDeliverySites()) {
            outputFile << "   - " << city->getName() << " (" << city->getCode() << ")" << ": "
                       << flowManager.getMaxFlow(city->getCode()) << " (m3/s) " << endl;
        }
        outputFile.close(); // Close the file
    }

    cout << "\n***********************************************************\n";
    cout << "\n Flow getting to each city: \n";
    Dataset *dataset = Dataset::getInstance();
    for (auto city: dataset->getGraph().getDeliverySites()) {
        cout << "   - " << city->getName() << " (" << city->getCode() << ")" << ": "
             << flowManager.getMaxFlow(city->getCode()) << " (m3/s) " << endl;
    }
    printFooterOption();
}

/**
 * @brief Displays the cities with water needs
 */
void MetricsMenu::showWaterNeeds() {
    ofstream outputFile("output.txt", ios::app); // Open the file in append mode
    if (outputFile.is_open()) {
        Dataset *dataset = Dataset::getInstance();
        outputFile << "\n***********************************************************\n";
        outputFile << "\n Water needs for current configuration: \n";
        for (const auto &value: flowManager.getWaterNeeds()) {
            outputFile << "   - " << dataset->getNodeName(value.first) << " (" << value.first << ")" << ": needs "
                       << value.second
                       << " (m3/s) " << endl;
        }
        outputFile.close(); // Close the file
    }

    Dataset *dataset = Dataset::getInstance();
    cout << "\n***********************************************************\n";
    cout << "\n Water needs for current configuration: \n";

    for (const auto &value: flowManager.getWaterNeeds()) {
        cout << "   - " << dataset->getNodeName(value.first) << " (" << value.first << ")" << ": needs " << value.second
             << " (m3/s) " << endl;
    }
    printFooterOption();
}

/**
 * @brief Displays the metrics before and after the balance
 */
void MetricsMenu::showBalanceFlow() {
    ofstream outputFile("output.txt", ios::app); // Open the file in append mode

    flowManager.getMaxFlow();

    // Before balancing load
    Metrics preBalanceMetrics = flowManager.calculateMetrics();
    std::cout << "Metrics before load balancing:\n";
    outputFile << "Metrics before load balancing:\n";
    std::cout << "  ->Average Difference: " << preBalanceMetrics.averageDifference << "\n";
    outputFile << "  ->Average Difference: " << preBalanceMetrics.averageDifference << "\n";
    std::cout << "  ->Variance: " << preBalanceMetrics.variance << "\n";
    outputFile << "  ->Variance: " << preBalanceMetrics.variance << "\n";
    std::cout << "  ->Max Difference: " << preBalanceMetrics.maxDifference << "\n";
    outputFile << "  ->Max Difference: " << preBalanceMetrics.maxDifference << "\n";

    // Balance the load
    Metrics postBalanceMetrics = flowManager.balanceLoad();

    // After balancing load
    std::cout << endl << "Metrics after load balancing:\n";
    outputFile << endl << "Metrics after load balancing:\n";
    std::cout << "  ->Average Difference: " << postBalanceMetrics.averageDifference << "\n";
    outputFile << "  ->Average Difference: " << postBalanceMetrics.averageDifference << "\n";
    std::cout << "  ->Variance: " << postBalanceMetrics.variance << "\n";
    outputFile << "  ->Variance: " << postBalanceMetrics.variance << "\n";
    std::cout << "  ->Max Difference: " << postBalanceMetrics.maxDifference << "\n";
    outputFile << "  ->Max Difference: " << postBalanceMetrics.maxDifference << "\n";

    outputFile.close();

    flowManager.getMaxFlow();

    printFooterOption();
}
