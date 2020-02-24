#include "adjacencylist.h"
#include "origincity.h"

AdjacencyList::AdjacencyList() {

}

AdjacencyList::~AdjacencyList() {

}

DLList<OriginCity>& AdjacencyList::getData() {
    return data;
}

void AdjacencyList::addFlight(DSString city1, DSString city2, DSString airline, int cost, int time) {
    int counter = 0;
    data.resetCurrent();
    while (data.getCurrent() != nullptr) {
        if (data.getCurrent()->getData().getName() == city1) {
            counter ++;
            data.getCurrent()->getData().addConnection(city2,airline, cost,time);
        }
        data.incCurrent();
    }
    if (counter == 0) {
        OriginCity temp(city1);
        temp.addConnection(city2,airline,cost,time);
        data.push_back(temp);
    }
}


