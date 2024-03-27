//
// Created by jpnsantos on 21/03/24.
//
#include "ReliabilityMenu.h"
#include "MainMenu.h"
#include "managers/ReliabilityManager.h"

void ReliabilityMenu::display() {
    system("clear");
    cout << "****************************************************************************************\n"
         << "*     Reliability and sensitivity                                                      *\n"
         << "*                                                                                      *\n"
         << "*     1) Reservoirs Reliability                                                        *\n"
         << "*     2) Stations Reliability                                                          *\n"
         << "*     3) Pipes Reliability                                                             *\n"
         << "*                                                                                      *\n"
         << "*                                                                              0) Back *\n"
         << "****************************************************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || (option < 0 || option > 3)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch (option) {
        case 1:
            showReservoirsReliability();
            break;
        case 2:
            showStationsReliability();
            break;
        case 3:
            showPipelineReliability();
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

void ReliabilityMenu::showReservoirsReliability() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();
    string code;
    cout << "Enter reservoir code: ";
    cin >> code;
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    cout << "\n***********************************************************\n";
    cout << "\nCities affected by the removal of " << dataset->getReservoirName(code) << " (" << code << ")" << ":\n";


    vector<pair<string, double>> affectedCities = reliabilityManager.evaluateReservoirImpact(code);


    if (affectedCities.empty()) {
        cout << "No cities affected by the removal of this reservoir." << endl;
    } else {

        for (const auto &city: affectedCities) {
            cout << "\n - " << dataset->getNodeName(city.first) << " (" << city.first << ")" << ": "
                 << city.second
                 << " (m3/s) " << endl;
        }
    }

    printFooterOption();
}

void ReliabilityMenu::showStationsReliability() {
    system("clear");
    cout << "****************************************************************************************\n"
         << "*     Stations Reliability                                                             *\n"
         << "*                                                                                      *\n"
         << "*     1) Non-affecting Stations                                                        *\n"
         << "*     2) Affecting Stations                                                            *\n"
         << "*     3) Cities affected by a specific station                                         *\n"
         << "*                                                                                      *\n"
         << "*                                                                                      *\n"
         << "*                                                                              0) Back *\n"
         << "****************************************************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || (option < 0 || option > 3)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch (option) {
        case 1:
            showNoAffectingStations();
            break;
        case 2:
            showAffectingStations();
            break;
        case 3:
            showCitiesAffectedByStation();
            break;
        case 0:
            backToMain();
            break;
    }
}

void ReliabilityMenu::showNoAffectingStations() {
    cout << "\n***********************************************************\n";
    cout << "\nStations that do not affect any city:\n";
    Dataset *dataset = Dataset::getInstance();
    Graph g = dataset->getGraph();
    for (auto s: g.getStations()) {
        vector<pair<string, double>> res = reliabilityManager.evaluateStationImpact(s->getCode());
        if (res.empty()) {
            cout << "- " << s->getCode() << endl;
        }
    }

    printFooterOption();
}

void ReliabilityMenu::showAffectingStations() {
    cout << "\n***********************************************************\n";
    cout << "\nStations that affect cities:\n";
    Dataset *dataset = Dataset::getInstance();
    Graph g = dataset->getGraph();
    for (auto s: g.getStations()) {
        vector<pair<string, double>> res = reliabilityManager.evaluateStationImpact(s->getCode());
        if (!res.empty()) {
            cout << s->getCode() << endl;
            for (const auto &city: res) {
                cout << " - " << city.first << ": "
                     << city.second
                     << " (m3/s) " << endl;
            }
        }
    }

    printFooterOption();
}

void ReliabilityMenu::showCitiesAffectedByStation() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();
    string code;
    cout << "Enter station code: ";
    cin >> code;
    transform(code.begin(), code.end(), code.begin(), ::toupper);
    cout << "\n***********************************************************\n";
    cout << "\nCities affected by the removal of " << code << ":\n";


    vector<pair<string, double>> affectedCities = reliabilityManager.evaluateStationImpact(code);


    if (affectedCities.empty()) {
        cout << "No cities affected by the removal of this station." << endl;
    } else {

        for (const auto &city: affectedCities) {
            cout << "\n - " << city.first << ": "
                 << city.second
                 << " (m3/s) " << endl;
        }
    }

    printFooterOption();
}

void ReliabilityMenu::showPipelineReliability() {
    system("clear");
    cout << "****************************************************************************************\n"
         << "*     Pipeline Reliability                                                             *\n"
         << "*                                                                                      *\n"
         << "*     1) Cities affected by each pipe                                                  *\n"
         << "*     2) Pipes that affect each city                                                   *\n"
         << "*                                                                                      *\n"
         << "*                                                                              0) Back *\n"
         << "****************************************************************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || (option < 0 || option > 2)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch (option) {
        case 1:
            showAffectingPipes();
            break;
        case 2:
            showAffectedCities();
            break;
        case 0:
            backToMain();
            break;
    }
}

void ReliabilityMenu::showAffectingPipes() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();
    vector<pair<string, string>> pipes = dataset->getPipes();

    if (pipes.empty()) {
        cout << "No pipelines available." << endl;
        printFooterOption();
        return;
    }

    cout << "Pipeline Failures:\n";


    for (const auto &pipe: pipes) {
        cout << "Pipeline from " << pipe.first << " to " << pipe.second
             << ":\n";


        vector<pair<string, double>> affectedCities = reliabilityManager.evaluatePipeImpact(pipe.first, pipe.second);


        if (!affectedCities.empty()) {
            for (const auto &city: affectedCities) {
                string cityName = dataset->getNodeName(city.first);
                cout << "City Name: " << cityName << ", City Code: " << city.first << ", Water Supply Deficit: "
                     << city.second << endl;

            }
        }

        cout << "----------------------------------------\n";
    }

    printFooterOption();
}

void ReliabilityMenu::showAffectedCities() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();

    Graph g = dataset->getGraph();
    for (auto city: g.getDeliverySites()) {
        cout << "City " << city->getName() << " (" << city->getCode() << ") "
             << ":\n";


        vector<pair<pair<string, string>, double>> affectingPipes = reliabilityManager.evaluateCityImpactByPipes(
                city->getCode());


        if (!affectingPipes.empty()) {
            for (const auto pipe: affectingPipes) {
                cout << "Pipe source: " << pipe.first.first << ", Pipe dest: " << pipe.first.second
                     << ", Water Supply Deficit: "
                     << pipe.second << endl;

            }
        }

        cout << "----------------------------------------\n";
    }

    printFooterOption();
}


