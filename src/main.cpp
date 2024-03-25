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
    //menu->display();

    FlowManager flowManager;
    Metrics initialMetrics = flowManager.calculateMetrics();
    cout << "Initial metrics:" << endl;
    cout << "Average difference: " << initialMetrics.averageDifference << endl;
    cout << "Variance: " << initialMetrics.variance << endl;

    Metrics improvedMetrics = flowManager.balanceLoad();
    cout << "Improved metrics after load balancing:" << endl;
    cout << "Average difference: " << improvedMetrics.averageDifference << endl;
    cout << "Variance: " << improvedMetrics.variance << endl;


}
