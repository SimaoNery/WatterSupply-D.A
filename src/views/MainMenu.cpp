
#include "MainMenu.h"
#include "MetricsMenu.h"
#include "FailuresMenu.h"

void MainMenu::display() {
    system("clear");
    cout << "**********************************************\n"
         << "*                                            *\n"
         << "*         Water Supply Management            *\n"
         << "*                                            *\n"
         << "*     1) BASIC SERVICE METRICS               *\n"
         << "*     2) RELIABILITY TO FAILURES             *\n"
         << "*     0) EXIT                                *\n"
         << "*                                            *\n"
         << "**********************************************\n"
         << "Option: ";
    int option;
    while (!(cin >> option) || (option != 0 && option != 1 && option != 2)) {
        cin.clear(); // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignore the invalid input
        cout << "Invalid option, please try again: ";
    }
    switch (option) {
        case 1: {
            MetricsMenu metricsMenu;
            metricsMenu.display();
            break;
        }
        case 2: {
            FailuresMenu failuresMenu;
            failuresMenu.display();
            break;
        }
        case 0:
            exit(0);
    }
}

void MainMenu::backToMain() {
    system("clear");
    MainMenu mainMenu;
    mainMenu.display();
}