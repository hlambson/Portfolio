//
// Created by henry on 3/2/2020.
//

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

void community::readInPaths(string l) {
    ifstream file;
    file.open(l);
    if (!file.is_open()) {
        cout << "error, path file didnt open" << endl;
    }
    char* buffer = new char[500]; //get number
    file.getline(buffer,500);
    buffer = strtok(buffer, "[]");
    int num = atoi(buffer);
    int x = 0;
    string line;
    string line2;
    while (x < num) {
        getline(file,line);
        storage<string> tempObj(line);
        paths.insert(line,tempObj); //insert into map
        node tempNode(line);
        nodes.push_back(tempNode); //put the nodes in the vector
        x++;
    }
    file.getline(buffer,50); //get the line that tells what type of graph it is
    buffer = strtok(buffer, "[]");
    bool directed = false;
    if (strcmp(buffer,"directed") == 0) {
        directed = true;
    }
    while(!file.eof()) {
        file >> line; //get the starting node
        file >> line2; //get rid of the dash
        file.getline(buffer, 50); //get the ending node
        buffer = strtok(buffer, " ");
        line2 = buffer;
        storage<string> temp(line, line2); //make a temp storage object
        edge tempEdge(line,line2);
        total.push_back(tempEdge);
        paths.insert(line,temp); //and insert into the map
        if (directed == false) {
            storage<string> temp2(line2,line);
            paths.insert(line2, temp2);
        }
    }
}

vector<edge> community::bfs(string start) {
    vector<edge> edges;
    int i = 2; //counter variable
    queue<string> list;
    for (int x = 0; x < nodes.size(); x++) {
        nodes[x].setVal(0); //reset all node values to 0
        if (nodes[x].getName() == start) {
            nodes[x].setVal(1); //set the value of the starting node to 1
            list.push(nodes[x].getName()); //push the starting node onto the queue
        }
    }
    while (!list.empty()) {
        string key = list.front(); //store the front value in the queue
        list.pop(); //then pop it off
        auto itr = paths.find(key);
        storage<string> temp = itr->second;
        for (int x = 0; x < temp.getConnections().size(); x++) {
            for (int y = 0; y < nodes.size(); y++) {
                if (temp.getConnections()[x] == nodes[y].getName()) {
                    if (nodes[y].getVal() == 0) {//set the value for the nodes connected to the current node if they arent set alreadu
                        nodes[y].setVal(i);
                        i++;
                        list.push(nodes[y].getName()); //queue the next node
                        edge tempEdge(key,nodes[y].getName());
                        edges.push_back(tempEdge); //push back the found edge
                    }
                }
            } //end inner for
        }// end outer for
    }// end while

    return edges;
}

vector<edge> community::dfs(string start) {
    vector<edge> edges;
    int i = 2; //counter variable
    stack<string> list;
    for (int x = 0; x < nodes.size(); x++) {
        nodes[x].setVal(0); //reset all node values to 0
        if (nodes[x].getName() == start) {
            nodes[x].setVal(1); //set the value of the starting node to 1
            list.push(nodes[x].getName()); //push the starting node onto the stack
        }
    }
    while (!list.empty()) {
        string key = list.top(); //store the front value in the queue
        list.pop(); //then pop it off
        auto itr = paths.find(key);
        storage<string> temp = itr->second;
        for (int x = 0; x < temp.getConnections().size(); x++) {
            for (int y = 0; y < nodes.size(); y++) {
                if (temp.getConnections()[x] == nodes[y].getName()) {
                    if (nodes[y].getVal() == 0) {//set the value for the nodes connected to the current node if they arent set alreadu
                        nodes[y].setVal(i);
                        i++;
                        list.push(nodes[y].getName()); //push the next node
                        edge tempEdge(key,nodes[y].getName());
                        edges.push_back(tempEdge); //push back the found edge
                    }
                }
            } //end inner for
        }// end outer for
    }// end while

    return edges;
}

vector<edge> community::bfsModified(string start) {
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

stack<edge> community::makeConnection(string start, string end) {
    vector<edge> edges = bfs(start);
    stack<edge> currPath;
    vector<edge> options;
    for (int x = 0; x < edges.size(); x++) { //if the starting node has multiple edges attached to it
        if (edges[x].getName1() == start) {
            options.push_back(edges[x]);
        }
    }

    edge current;
    edge previous;
    int x = 0;
    bool check;
    for (int index = 0; index < options.size(); index++) { //backtracking to find all the paths to the end node
        currPath.push(options[index]);
        while (!currPath.empty()) {
                x = 0;
            if (currPath.top() == current) {
                previous = currPath.top();
                currPath.pop();
            }
            else {
                if (currPath.top().getName2() == end) { //if the first edge leads to the end node
                    return currPath;
                } else {
                    current = currPath.top();
                    while (x < edges.size()) {
                        check = false;
                        if (currPath.top().getName2() == edges[x].getName1() && edges[x] != previous) { //check if the edges connect and make sure it doesnt add what was just popped off
                            currPath.push(edges[x]);
                            if (currPath.top().getName2() == end) { //check if what was added is the end node and push the path if it is
                                return currPath;
                            }
                            x = 0;
                            check = true;
                        }
                        if (check == false) {
                            x++;
                        }
                    } //end inner while
                    previous = currPath.top();
                    currPath.pop();
                }
            }
        } //end outer while
    }//end for
    return currPath;
}

void community::printConnection(string start, string end) {
    stack<edge> path = makeConnection(start,end);

    if (path.empty()) {
        output << "Could not find a path for those nodes. Maybe try a different pair of nodes?" << endl;
    }
    else {
        stack<edge> reverse;
        int size = path.size();
        for (int x = 0; x < size; x++) { //reverse the stack
            reverse.push(path.top());
            path.pop();
        }
        size = reverse.size();
        output << "{";
        for (int x = 0; x < size; x++) { //print out the path
            if (x == size - 1) {
                output << "(" << reverse.top().getName1() << "," << reverse.top().getName2() << ")}";
            } else {
                output << "(";
                output << reverse.top().getName1() << ",";
                output << reverse.top().getName2() << "), ";

            }
            reverse.pop();

        }
        output << endl;
    }
    output << endl;
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

void community::control(char* f) {
    ifstream file;
    file.open(f);
    if (!file.is_open()) {
        cout << "control file didnt open" << endl;
    }
    string buffer;
    char* line = new char[500];
    while(!file.eof()) {
        file >> buffer;

        if (buffer == "or") {

            file.getline(line,500);
            line = line + 1;
            readInPaths(line);
        }
        if (buffer == "ow") {
            file.getline(line,500);
            line = line + 1;
            output.open(line);
            if(!output.is_open()) {
                cout << "output didnt open " << endl;
            }
        }
        if (buffer == "dfs") {
            file.getline(line,500);
            line = line + 1;
            vector<edge> depth = dfs(line);
            output << "DEPTH" << endl;
            for (int x = 0; x < depth.size(); x++) {
                output << depth[x].getName1() << " - " << depth[x].getName2() << endl;
            }
            output << endl;

        }
        if (buffer == "bfs") {
            file.getline(line,500);
            line = line + 1;
            vector<edge> breadth = bfs(line);
            output << "BREADTH" << endl;
            for (int x = 0; x < breadth.size(); x++) {
                output << breadth[x].getName1() << " - " << breadth[x].getName2() << endl;
            }
            output << endl;
        }
        if (buffer == "mc") {
            char* line2 = new char[500];
            file >> line;
            file.getline(line2,500);
            line2 = line2 + 1;
            printConnection(line, line2);
        }
        if (buffer == "dc") {
            removeEdges();
        }
    }
}
