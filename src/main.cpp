#include <iostream>
#include "utils/Dataset.h"
#include "managers/FlowManager.h"
#include "views/Menu.h"
#include "views/MainMenu.h"
#include "managers/ReliabilityManager.h"

using namespace std;

int main() {
    cout << "Loading dataset..." << endl;
    Dataset *dataset = Dataset::getInstance();
    Menu *menu;
    // Point to main menu
    menu = new MainMenu();
    //menu->display();

    // test evaluation
    ReliabilityManager reliabilityManager;

    cout << "Evaluating reservoir impact..." << endl;
    for (auto r: dataset->getGraph().getReservoirs()) {
        vector<pair<string, double>> res = reliabilityManager.evaluateReservoirImpact(r->getCode());
        cout << "Reservoir " << r->getCode() << " impact: " << endl;
        for (auto city: res) {
            cout << "   - " << dataset->getCityName(city.first) << " (" << city.first << "): " << city.second << endl;
        }
    }
}
