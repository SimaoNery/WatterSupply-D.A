#include <iostream>
#include "utils/Dataset.h"

int main() {
    Dataset *dataset = Dataset::getInstance();

   /* The way this is being sortes is messy *MUST REVIEW*
   for (const auto &item: dataset->getStations()) {
        cout << item.getId() << " " << item.getCode() << endl;
   }
    */
    /*
    for(const auto &item : dataset->getDeliverySites()){
        cout << item.getName() << " " << item.getId() << " " << item.getCode() << " " << item.getDemand() << " " << item.getPopulation() << endl;
    }
    */

    return 0;
}
