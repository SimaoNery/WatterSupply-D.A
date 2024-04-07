//
// Created by jpnsantos on 21/03/24.
//

#ifndef DA_WATER_SUPPLY_MENU_H
#define DA_WATER_SUPPLY_MENU_H

/**
 * Abstract base class for all menu classes.
 * Provides a common interface for displaying menus.
 */
class Menu {
public:
     // Pure virtual function for displaying a menu. Must be overridden in derived classes.
    virtual void display() = 0;
};

#endif //DA_WATER_SUPPLY_MENU_H
