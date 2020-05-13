//
// Created by henry on 3/2/2020.
//
//Girvan-Newman Algorithm
#include "community.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include "edge.h"
using namespace std;
community::community() {

}

community::~community() {

}


vector<edge> community::bfsModified(string start) { //breadth first search
    vector<edge> edges;
    vector<node*> pointers;
    for (int x = 0; x < nodes.size(); x++) {
        nodes[x].setWeight(0);
        nodes[x].setDistance(0);
        nodes[x].setNum(0);
        pointers.push_back(&nodes[x]);
    }
    int i = 2; //counter variable
    queue<node*> list;
    for (int x = 0; x < pointers.size(); x++) {
        pointers[x]->setVal(0); //reset all node values to 0
        if (pointers[x]->getName() == start) {
            pointers[x]->setVal(1); //set the value of the starting node to 1
            pointers[x]->setDistance(0);
            pointers[x]->setNum(0);
            list.push(pointers[x]); //push the starting node onto the queue
        }
    }
    while (!list.empty()) {
        node* previous = list.front(); //store the front value in the queue
        list.pop(); //then pop it off
        auto itr = paths.find(previous->getName());
        storage<string> temp = itr->second;
        for (int x = 0; x < temp.getConnections().size(); x++) {
            for (int y = 0; y < pointers.size(); y++) {
                if (temp.getConnections()[x] == pointers[y]->getName()) {
                    if (pointers[y]->getVal() == 0 || (previous->getDistance() + 1) == pointers[y]->getDistance() ) {//set the value for the nodes connected to the current node if they arent set alreadu
                        if (pointers[y]->getVal() == 0) {
                            pointers[y]->setVal(i);
                            pointers[y]->setDistance(previous->getDistance() + 1);
                            if (previous->getNum() == 0) {
                                pointers[y]->setNum(1);
                            }
                            else {
                                pointers[y]->setNum(previous->getNum());
                            }
                            i++;
                            list.push(pointers[y]); //push the next node
                        }
                        else {
                            pointers[y]->setVal(i);
                            pointers[y]->setDistance(previous->getDistance() + 1);
                            if (previous->getNum() == 0) {
                                pointers[y]->setNum(1);
                            } else {
                                pointers[y]->setNum(previous->getNum());
                            }
                        }
                        string tempStr = previous->getName() + pointers[y]->getName();
                        bool check = false;
                        for (int x = 0; x < edges.size(); x++) {
                            if ((edges[x].getName1() + edges[x].getName2()) == tempStr) {
                                check = true;
                            }
                        }
                        if (check == false) {
                            edge tempEdge(previous->getName(),pointers[y]->getName());
                            edges.push_back(tempEdge); //push back the found edge
                        }
                    }
                }
            } //end inner for
        }// end outer for
    }// end while
    nodes.clear();
    for (int x = 0; x < pointers.size(); x++) {
        nodes.push_back(*pointers[x]);
    }
    return edges;
}

void community::discoverCommunities() {
    for (int x = 0; x < nodes.size(); x++) {
        vector<edge> edges = bfsModified(nodes[x].getName());
        stack<edge> tracker;

        for (int y = 0; y < nodes.size(); y++) {
            storage<string> tempStore(nodes[y].getName());
            nodes[y].setWeight(1);
        }
        for (int y = 0; y < edges.size(); y++) {
            storage<string> tempStore(edges[y].getName1(), edges[y].getName2());
            tracker.push(edges[y]);
        }

         while(!tracker.empty()) {
             edge temp = tracker.top();
             tracker.pop();
             double numPrev;
             for (int y = 0; y < nodes.size(); y++) {
                 if (nodes[y].getName() == temp.getName1()) {
                     numPrev = nodes[y].getNum();
                 }

             }
             int index = 0;
             for(int i = 0; i < nodes.size(); i++) {
                 if (nodes[i].getName() == temp.getName2()) {
                     for (int y = 0; y < total.size(); y++) {
                         if ((temp.getName1() == total[y].getName1() && temp.getName2() == total[y].getName2()) || (temp.getName2() == total[y].getName1() && temp.getName1() == total[y].getName2())) {
                             if (numPrev == 0) {
                                 total[y].setBetweenness((nodes[i].getWeight()));
                             }
                             else {
                                 total[y].setBetweenness(nodes[i].getWeight() * (numPrev / nodes[i].getNum()));
                                 total[y].setWeight(nodes[i].getWeight() * (numPrev / nodes[i].getNum()));
                             }
                             index = y;

                         }
                     }
                 }
             }

             for (int i = 0; i < nodes.size(); i++) {
                 if (nodes[i].getName() == temp.getName1()) {
                         nodes[i].setWeight(total[index].getWeight());
                 }
             }
         }
    }
}

void community::removeEdges() {
    discoverCommunities();
    double max = total[0].getBetweenness();
    int index = 0;
    double sumBet = 0;
    int counter = 0;
    int number = total.size() * .3;
    int c1 = 0;
    int c2 = 0;
    for (int x = 0; x < number; x++) {
        double max = total[0].getBetweenness();
        int index = 0;
        for (int y = 0; y < total.size(); y++) {
            if (total[y].getBetweenness() > max) {
                max = total[y].getBetweenness(); //find the edge with the highest betweeness
                index = y;
            }
        }


        auto itr = paths.find(total[index].getName1());
        for (int z = 0; z < itr->second.getConnections().size(); z++) {
            if (itr->second.getConnections().at(z) == total[index].getName2()) { //then remove it
                itr->second.getConnections().erase(itr->second.getConnections().begin() + z);
                c2++;
            }
        }
        total.erase(total.begin() + index);
        c1++;
    }
    int x = 0;
    for (int q = 0; q < nodes.size(); q++) {
        nodes[q].setVisited(0);
    }
    while (x < nodes.size()) {
        if (nodes[x].getVisited() == 0) {
            output << "Community: " << endl;
            vector<edge> com = bfsModified(nodes[x].getName());
            for (int y = 0; y < com.size(); y++) {
                for (int z = 0; z < nodes.size(); z++) {
                    if (com[y].getName1() == nodes[z].getName() || com[y].getName2() == nodes[z].getName()) {
                        if (nodes[z].getVisited() == 0 ) {
                            output << nodes[z].getName() << endl;
                        }
                        nodes[z].setVisited(1);

                    }
                }
            }
            output << endl;
        }
        x++;
    }

}
