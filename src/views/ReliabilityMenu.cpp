//
// Created by jpnsantos on 21/03/24.
//

#include "ReliabilityMenu.h"
#include "MainMenu.h"

void ReliabilityMenu::display() {
    cout << "****************************************************************************************\n"
         << "*   reliability and sensitivity to failures                                            *\n"
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
        //case 1:
        //    showMenu();
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