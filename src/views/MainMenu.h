//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_MAINMENU_H
#define DA_WATER_SUPPLY_MAINMENU_H


#include <iostream>

#include "Menu.h"
#include "utils/Dataset.h"

using namespace std;

class MainMenu : public Menu {
public:
    void display() override;

    static void backToMain(); // Add this line
};


#endif //DA_WATER_SUPPLY_MAINMENU_H
