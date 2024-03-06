#include <iostream>
#include "utils/Dataset.h"

int main() {
    Dataset *dataset = Dataset::getInstance();
    cout << "Hello, World!" << endl;
    for (const auto &item: dataset->getStations()) {
        cout << item.getId() << " " << item.getCode() << endl;
    }
    return 0;
}
