//
// Created by jpnsantos on 21/03/24.
//

#include "ReliabilityMenu.h"
#include "MainMenu.h"
#include "managers/ReliabilityManager.h"

void ReliabilityMenu::display() {
    cout << "****************************************************************************************\n"
         << "*     Reliability and sensitivity                                                      *\n"
         << "*                                                                                      *\n"
         << "*     1) To removing one specific water reservoir                                      *\n"
         << "*     2) To removing pumping stations                                                  *\n"
         << "*     3) If pipeline failures can occur                                                *\n"
         << "*                                                                                      *\n"
         << "*                                                                                      *\n"
         << "*                                                                              0) Back *\n"
         << "****************************************************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || (option < 0 || option > 4)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch (option) {
        case 1:
            showRemovingReservoir();
            break;
        case 2:
            showRemovingStations();
            break;
        case 3:
            showPipelineFails();
            break;
        case 0:
            backToMain();
            break;
    }
}

/*
 void ReliabilityMenu::showMenu() {
    ReliabilityManager reliabilityManager;

    reliabilityManager.evaluateReservoirImpact();
}

*/

/**
 * @brief Navigates back to the main menu.
 */
void ReliabilityMenu::backToMain() {
    MainMenu mainMenu;
    mainMenu.display();
}

/**
 * @brief Displays the footer option and handles user input.
 */
void ReliabilityMenu::printFooterOption() {
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

void ReliabilityMenu::showRemovingReservoir() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();
    string code;
    cout << "Enter reservoir code: ";
    cin >> code;
    cout << "\n***********************************************************\n";
    cout << "\nCities affected by " << dataset->getReservoirName(code) << " (" << code << ")" << ":\n";


    vector<pair<string, double>> affectedCities = reliabilityManager.evaluateReservoirImpact(code);


    if (affectedCities.empty()) {
        cout << "No cities affected by the removal of this reservoir." << endl;
    } else {

        for (const auto &city : affectedCities) {
            string cityName = dataset->getCityName(city.first);
            cout << "City Name: " << cityName  << endl;
        }
    }

    printFooterOption();
}

void ReliabilityMenu::showRemovingStations() {
    cout << "\n***********************************************************\n";
    cout << "List of Stations:\n";

    Dataset *dataset = Dataset::getInstance();
    vector<pair<int, string>>& stations = dataset->stations;

    for (size_t i = 0; i < stations.size(); ++i) {
        cout << i + 1 << ". " << stations[i].second << endl;
    }

    int choice;
    cout << "Enter the station number to see affected cities: ";
    cin >> choice;

    if (choice < 1 || choice > static_cast<int>(stations.size())) {
        cout << "Invalid station number. Please try again." << endl;
        return;
    }

    vector<pair<string, double>> affectedCities = reliabilityManager.evaluateStationImpact(stations[choice - 1].second);

    cout << "\n***********************************************************\n";
    cout << "Affected Cities by Station " << stations[choice - 1].second << ":\n";

    if (affectedCities.empty()) {
        cout << "No cities affected." << endl;
    } else {
        for (const auto& city : affectedCities) {
            string cityName = dataset->getCityName(city.first); // Obter o nome da cidade
            cout << "City Name: " << cityName << ", Deficit: " << city.second << endl;
        }
    }

    printFooterOption();
}

void ReliabilityMenu::showPipelineFails() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();
    vector<pair<string, string>> pipes = dataset->getPipes();

    if (pipes.empty()) {
        cout << "No pipelines available." << endl;
        printFooterOption();
        return;
    }

    cout << "Pipeline Failures:\n";


    for (const auto& pipe : pipes) {
        cout << "Pipeline from " << dataset->getCityName(pipe.first) << " to " << dataset->getCityName(pipe.second) << ":\n";


        vector<pair<string, double>> affectedCities = reliabilityManager.evaluatePipeImpact(pipe.first, pipe.second);


        if (affectedCities.empty()) {
            cout << "No affected cities." << endl;
        } else {

            for (const auto& city : affectedCities) {
                string cityName = dataset->getCityName(city.first);
                cout << "City Name: " << cityName << ", City Code: " << city.first << ", Water Supply Deficit: " << city.second << ", Affected" << endl;

            }
        }

        cout << "----------------------------------------\n";
    }

    printFooterOption();
}


