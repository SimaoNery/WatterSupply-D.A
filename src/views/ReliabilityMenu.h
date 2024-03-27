//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_RELIABILITYMENU_H
#define DA_WATER_SUPPLY_RELIABILITYMENU_H

#include "Menu.h"
#include <iostream>
#include <limits>
#include "managers/ReliabilityManager.h"

using namespace std;

class ReliabilityMenu : public Menu {
public:
    /**
     * Displays the main menu for the statistics options.
     * Complexity: O(1), as the number of menu options is fixed.
     * @brief Displays the main menu and handles user input for the statistics options.
     * @see numberAirportsFlights(), flightsOutAirport(), flightsPerCityAirline(), airportToCountries(), numberDestinations(), numberDestinationXstops(), maxTrip(), topKAirports(), essentialAirports(), backToMain()
     * @return void
     */
    void display() override;

private:

    ReliabilityManager reliabilityManager;

    static void backToMain();

    void printFooterOption();

    void showNoAffectingStations();

    void showCitiesAffectedByStation();

    void showAffectingStations();

    void showStationsReliability();

    void showPipelineReliability();

    void showReservoirsReliability();

    void showAffectingPipes();

    void showAffectedCities();
};

#endif //DA_WATER_SUPPLY_RELIABILITYMENU_H
