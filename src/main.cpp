#include <iostream>
#include "utils/Dataset.h"
#include "managers/FlowManager.h"
#include "views/Menu.h"
#include "views/MainMenu.h"

using namespace std;

int main() {
    cout << "Loading dataset..." << endl;
    Dataset *dataset = Dataset::getInstance();
    Menu *menu;
    // Point to main menu
    menu = new MainMenu();
    menu->display();
}
