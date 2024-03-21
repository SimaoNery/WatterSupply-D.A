#include <iostream>
#include "utils/Dataset.h"
#include "managers/FlowManager.h"

using namespace std;

int main() {
    Dataset *dataset = Dataset::getInstance();
    FlowManager flowManager;

    cout << flowManager.getMaxFlow() << endl;

    for (const auto &value: flowManager.getWaterNeeds()) {
        cout << value.first << " -> " << value.second << endl;
    }

    return 0;
}
