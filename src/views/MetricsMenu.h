//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_METRICSMENU_H
#define DA_WATER_SUPPLY_METRICSMENU_H


#include "Menu.h"
#include <iostream>
#include <limits>

using namespace std;

class MetricsMenu : public Menu {
public:
    /**
     * Displays the main menu for the statistics options.
     * Complexity: O(1), as the number of menu options is fixed.
     * @brief Displays the main menu and handles user input for the statistics options.
     * @see numberAirportsFlights(), flightsOutAirport(), flightsPerCityAirline(), airportToCountries(), numberDestinations(), numberDestinationXstops(), maxTrip(), topKAirports(), essentialAirports(), backToMain()
     * @return void
     */
    void display() override {
        cout << "****************************************************************************************\n"
             << "*   basic service metrics                                                              *\n"
             << "*                                                                                      *\n"
             << "*     1)                                                                               *\n"
             << "*                                                                                      *\n"
             << "*                                                                              0) Back *\n"
             << "****************************************************************************************\n"
             << "Option: ";
        int option;
        while (!(cin >> option) || (option < 0 || option > 9)) {
            cin.clear(); // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
            cout << "Invalid option, please try again: ";
        }
        switch (option) {
            case 0:
                backToMain();
                break;
        }
    }

private:

    static void backToMain();

    void printFooterOption();
};


#endif //DA_WATER_SUPPLY_METRICSMENU_H
