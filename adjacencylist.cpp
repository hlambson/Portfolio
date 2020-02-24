#include "adjacencylist.h"
#include "origincity.h"
//this is a custom adjacency list class that was used in a program in my data structures class
//the program was to plan flights based on how fast or cost efficient it would be to get from one city to another
//I used an adjacency list to show what cities you could get to from where, so the outer list is a starting city and its inner list is 
//what cities you can get to from the starting city

//the OriginCity object holds a doubly linked list of city objects

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
        if (data.getCurrent()->getData().getName() == city1) { //check if the city is already in the list
            counter ++;
            data.getCurrent()->getData().addConnection(city2,airline, cost,time); //if it is, add to its inner list
        }
        data.incCurrent();
    }
    if (counter == 0) { //if the city is not already in the list, add it 
        OriginCity temp(city1);
        temp.addConnection(city2,airline,cost,time); //and add to its inner list
        data.push_back(temp);
    }
}


