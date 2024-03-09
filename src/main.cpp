#include <iostream>
#include "utils/Dataset.h"

int main() {
    Dataset *dataset = Dataset::getInstance();

    //This prints in a weird way since the hash functions are ordering this inside the unordered_maps

    /*Test stations
   for (const auto &item: dataset->getStations()) {
        cout << item.getId() << " " << item.getCode() << endl;
   }
    */

    /*Test DeliverySites
    for(const auto &item : dataset->getDeliverySites()){
        cout << item.getName() << " " << item.getId() << " " << item.getCode() << " " << item.getDemand() << " " << item.getPopulation() << endl;
    }
    */

    /*Test Reservoirs
    for(const auto &item : dataset->getReservoirs()){
        cout << item.getName() << " " << item.getDeliverySite() << " " << item.getId() << " " << item.getCode() << " " << item.getMaxDelivery() << endl;
    }
    */

    /*Test Vertexes
    for(auto vert : dataset->getGraph().getVertexSet()){
        cout << vert->getInfo().getCode() << endl;
    }
    */
    /*Test Edges
    int count = 0;
    for(auto vert :  dataset->getGraph().getVertexSet()){
        for(auto edge : vert->getAdj()){
            //cout << edge->getOrig()->getInfo().getCode() << " ----> " << edge->getDest()->getInfo().getCode() << endl; count++;

            auto destination = edge->getDest();
            cout << destination->getInfo().getCode()<< endl;
        }
    }
    cout << count << endl;
     //count == 208 : 173 given + 35 from bidirectional
    */

    return 0;
}
