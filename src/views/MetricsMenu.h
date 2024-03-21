//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_METRICSMENU_H
#define DA_WATER_SUPPLY_METRICSMENU_H


#include "Menu.h"
#include "managers/FlowManager.h"
#include <iostream>
#include <limits>

using namespace std;

class MetricsMenu : public Menu {
public:

    MetricsMenu();

    void showMaxFlow();

    void showNetworkFlow();

    void showFlowForCity();

    void showFlowForAllCities();

    void showWaterNeeds();

    void display() override;

private:
    FlowManager flowManager;

    static void backToMain();

    void printFooterOption();
};


#endif //DA_WATER_SUPPLY_METRICSMENU_H
