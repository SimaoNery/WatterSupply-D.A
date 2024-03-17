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
    DeliverySite ds = DeliverySite("A", 1, "A", 1, 1);
    cout << ds.getName() << endl;
    Vertex<Node> v = Vertex<Node>(ds);

    Node &node = v.getInfo();
    if (node.getType() == NodeType::DELIVERY_SITE) {
        // Access DeliverySite attributes
        cout << "Funcionou" << endl;
    }
/*
    for (auto vert: dataset->getGraph().getVertexSet()) {
        Node *node = &vert->getInfo();

        // Try to cast to DeliverySite
        auto *deliverySite = dynamic_cast<DeliverySite *>(node);

        if (deliverySite != nullptr) {
            // Access DeliverySite attributes
            std::cout << deliverySite->getName() << std::endl;
            continue;
        }

        // Try to cast to Reservoir
        auto *reservoir = dynamic_cast<Reservoir *>(node);
        if (reservoir != nullptr) {
            // Access Reservoir attributes
            std::cout << reservoir->getName() << std::endl;
            continue;
        }
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
