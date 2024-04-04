#include <iostream>
#include "utils/Dataset.h"
#include "managers/FlowManager.h"
#include "views/Menu.h"
#include "views/MainMenu.h"
#include "managers/ReliabilityManager.h"

using namespace std;

/**
 * @brief Main entry point of the application.
 *
 * This function is responsible for initializing the dataset, setting up the main menu, and starting the application.
 * It first prints a message indicating that the dataset is being loaded. Then, it retrieves an instance of the Dataset
 * singleton and initializes the main menu. Finally, it displays the main menu to start the application.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
    cout << "Loading dataset..." << endl;
    Dataset *dataset = Dataset::getInstance();
    Menu *menu;
    // Point to main menu
    menu = new MainMenu();
    menu->display();

    return 0;
}
