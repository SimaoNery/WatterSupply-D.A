#include <iostream>
#include "utils/Dataset.h"

int main() {
    Dataset *dataset = Dataset::getInstance();
    cout << "Hello, World!" << endl;
    for (const auto &item: dataset->getStations()) {
        std::cout << item.getCode() << std::endl;
    }
    return 0;
}
