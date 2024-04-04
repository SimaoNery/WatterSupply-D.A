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
         << "*     4) Reset Changes                                                                 *\n"
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
            showReservoirsReliability();
            break;
        case 2:
            showStationsReliability();
            break;
        case 3:
            showPipelineReliability();
            break;
        case 4:
            resetChanges();
        case 0:
            backToMain();
            break;
    }
}

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
    string cont = "YES";

    while (cont == "YES") {
        cout << "Enter reservoir code: ";
        cin >> code;
        transform(code.begin(), code.end(), code.begin(), ::toupper);
        cout << "\n***********************************************************\n";
        cout << "\nCities affected by the removal of " << dataset->getReservoirName(code) << " (" << code << ")"
             << ":\n";


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

        cout << endl << "Do you want to remove another reservoir? (yes/no)" << endl;
        cin >> cont;
        transform(cont.begin(), cont.end(), cont.begin(), ::toupper);
        cout << endl;
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
         << "*     4) Sequential Station Removal                                                    *\n"
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
            showNoAffectingStations();
            break;
        case 2:
            showAffectingStations();
            break;
        case 3:
            showCitiesAffectedByStation();
            break;
        case 4:
            sequentialStationRemoval();
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
        dataset->resetChanges();
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
        dataset->resetChanges();
        vector<pair<string, double>> res = reliabilityManager.evaluateStationImpact(s->getCode());
        if (!res.empty()) {
            cout << s->getCode() << endl;
            for (const auto &city: res) {
                cout << " - " << city.first << ": "
                     << city.second
                     << " (m3/s) " << endl;
            }
        }
        cout << endl;
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

    dataset->resetChanges();
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
         << "*     3) Sequential Pipe Removal                                                       *\n"
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
            showAffectingPipes();
            break;
        case 2:
            showAffectedCities();
            break;
        case 3:
            sequentialPipeRemoval();
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

    cout << "Pipeline Failures:\n" << endl;


    for (const auto &pipe: pipes) {
        cout << "Pipeline from " << pipe.first << " to " << pipe.second
             << ":\n";

        dataset->resetChanges();
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


void ReliabilityMenu::sequentialPipeRemoval() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();

    string source;
    string dest;
    string cont = "YES";

    while (cont == "YES") {
        cout << "Choose a source:";
        cin >> source;
        transform(source.begin(), source.end(), source.begin(), ::toupper);
        if(!dataset->getGraph().findVertex(source)){
            cout << "Invalid!";
            break;
        }
        cout << endl;

        cout << "Choose a destiny:";
        cin >> dest;
        transform(dest.begin(), dest.end(), dest.begin(), ::toupper);
        if(!dataset->getGraph().findVertex(source)){
            cout << "Invalid!";
            break;
        }
        cout << endl;

        vector<pair<string, double>> affectedCities = reliabilityManager.evaluatePipeImpact(source, dest);

        if (!affectedCities.empty()) {
            for (const auto &city: affectedCities) {
                string cityName = dataset->getNodeName(city.first);
                cout << "City Name: " << cityName << ", City Code: " << city.first << ", Water Supply Deficit: "
                     << city.second << endl;

            }
        } else if (affectedCities.empty()) {
            cout << "No cities affected!" << endl;
        }

        cout << "Do you want to remove another pipe? (yes | no)" << endl;
        cin >> cont;
        transform(cont.begin(), cont.end(), cont.begin(), ::toupper);
        cout << endl;
    }

    printFooterOption();
}

void ReliabilityMenu::sequentialStationRemoval() {
    cout << "\n***********************************************************\n";
    Dataset *dataset = Dataset::getInstance();

    string code;
    string cont = "YES";
    dataset->resetChanges();
    while (cont == "YES") {
        cout << "Choose a station:";
        cin >> code;
        transform(code.begin(), code.end(), code.begin(), ::toupper);
        if(!dataset->getGraph().findVertex(code)){
            cout << "Invalid!";
            break;
        }
        cout << endl;

        vector<pair<string, double>> affectedCities = reliabilityManager.evaluateStationImpact(code);

        if (!affectedCities.empty()) {
            for (const auto &city: affectedCities) {
                string cityName = dataset->getNodeName(city.first);
                cout << "City Name: " << cityName << ", City Code: " << city.first << ", Water Supply Deficit: "
                     << city.second << endl;

            }
        } else if (affectedCities.empty()) {
            cout << "No cities affected!" << endl;
        }

        cout << endl << "Do you want to remove another pipe? (yes | no)" << endl;
        cin >> cont;
        transform(cont.begin(), cont.end(), cont.begin(), ::toupper);
        cout << endl;
    }

    printFooterOption();
}

void ReliabilityMenu::resetChanges() {
    Dataset *dataset = Dataset::getInstance();
    dataset->resetChanges();
    cout << "Changes reset successfully." << endl;
    this->display();
}
