//
// Created by henry on 4/29/2020.
//

#include "salseman.h"
#include "fstream"
#include "DSStack.h"
#include <stack>
#include <cstring>
#include "dsstring.h"

salesman::salesman() {

}

void salesman::readIn(string f) {
    ifstream file;
    file.open(f);
    if (!file.is_open()) {
        cout << "graph file didnt open" << endl;
    }
    char* buffer = new char[10];
    file.getline(buffer,10);
    int num = atoi(buffer);
    int x = 0;
    string line;
    string line2;
    while(x < num) { //read in from file and populate adjacency list and node vector
       file >> line;
       file >> line2;
       file >> line2;
       node obj(line);
       node obj2(line2);

       file.getline(buffer, 10);
       double weight;
       weight = atoi(buffer);
       obj.setWeight(weight);
       obj2.setWeight(weight);
       storage<node> temp(line,obj2);
       map.insert(line,temp);

       storage<node> temp2(line2,obj);
       map.insert(line2,temp2);
       bool check1 = false;
       bool check2 = false;
       for (int y = 0; y < nodes.size(); y++) {
           if (nodes[y].getName() == line) {
               check1 = true;
           }
           if (nodes[y].getName() == line2) {
               check2 = true;
           }
       }
       if (check1 == false) {
           nodes.push_back(obj);
       }
       if (check2 == false) {
           nodes.push_back(obj2);
       }
       x ++;
    }
}

void salesman::trivial(string start) { //trivial solution - generate every path possible and choose the lowest weight
    DSStack<DSString> path; //using DSStack and DSVector because I gave them contains functions
    DSVector<DSStack<DSString>> allPaths;  //I tried using DSString to fix the seg fault issue with string, but it didnt work but I didn't switch them back
    stack<string> another; //this is just to view what the path stack has in it in the debugger
    stack<int> weights;
    vector<int> allWeights;
    int weight = 0;
    int tempWeight;
    path.push(start.c_str());
    another.push(start);
    auto itr = map.find(start);
    int num = map.getSize();
    while(!path.isEmpty()) { //backtracking algorithm to generate every path
        bool check = true;
        for (int x = 0; x < itr->second.getConnections().size(); x++) {
            //check if the path does not have the node and that the node has not been visited yet
            if (!path.contains(itr->second.getConnections()[x].getName().c_str()) && check == true && itr->second.getConnections()[x].getVisited() == 0) {
                path.push(itr->second.getConnections()[x].getName().c_str());
                another.push(itr->second.getConnections()[x].getName());
                weight += itr->second.getConnections()[x].getWeight(); //add to the total weight
                weights.push(itr->second.getConnections()[x].getWeight()); //store the weight of the current edge in order to subract it later
                itr->second.getConnections()[x].setVisited(1);
                check = false;
            }
        }
        if (check == true) { //if all edges have been exhausted from the current node
            auto itr2 = map.find(path.peek().c_str());
            for (int x = 0; x < itr2->second.getConnections().size(); x++) {
                itr2->second.getConnections()[x].setVisited(0); //set the current node's visited back to 0
            }
            path.pop(); //pop it off
            another.pop();
            if (weights.size() > 0) {
                weight -= weights.top(); //subtract the weight of the edge just popped
                weights.pop();
            }
            if (path.getSize() > 0) {
                itr = map.find(path.peek().c_str()); //get the next node
            }
        }
        else {
            if (path.getSize() == num) { //if the path has reached every node, meaning it is done
                if (!allPaths.contains(path)) { //check if the vector has that path already
                    int index = 0;
                    itr = map.find(path.peek().c_str());
                    for (int i = 0; i < itr->second.getConnections().size(); i++) {
                        if(strcmp(itr->second.getConnections()[i].getName().c_str(), start.c_str()) == 0) { //find the edge from the last node to the starting node
                            path.push(start.c_str());
                            another.push(start);
                            index = i;
                            weight += itr->second.getConnections()[i].getWeight(); //add that edge's weight
                            weights.push(itr->second.getConnections()[i].getWeight());
                        }
                    }
                    allPaths.push_back(path); //push back the path found
                    allWeights.push_back(weight); //and its total weight
                    path.pop(); //pop off the edge to the starting node
                    another.pop();
                    weight -= weights.top();
                    weights.pop();
                }
                auto itr3 = map.find(path.peek().c_str());
                for (int x = 0; x < itr3->second.getConnections().size(); x++) {
                    itr3->second.getConnections()[x].setVisited(0); //reset the visited attribute
                }
                path.pop(); //then pop off
                another.pop();
                weight -= weights.top();
                weights.pop();

            }
            itr = map.find(path.peek().c_str()); //get the next node
        }

    }
    int min = allWeights[0];
    int index = 0;
    for (int x = 0; x < allWeights.size(); x++) { //find the path with the lowest weight
        if(allWeights[x] < min) {
            min = allWeights[x];
            index = x;
        }
    }

    DSStack<DSString> truePath = allPaths[index];
    DSStack<DSString> reverse;
    while(!truePath.isEmpty()) { //reverse the stack
        reverse.push(truePath.peek());
        truePath.pop();
    }
    cout << "TRIVIAL SOLUTION PATH + WEIGHT:" << endl;
    while(!reverse.isEmpty()) {
        cout << reverse.peek() << endl;
        reverse.pop();
    }
    cout << min << endl << endl;

}

void salesman::nearestNeighbor(string start) { //nearest neighbor algorithm - pick the edge that has the lowest weight
    auto itr = map.find(start);
    storage<node> test;
    test = itr->second;
    int num = map.getSize();
    for (int x = 0; x < nodes.size(); x++) {
        if (nodes[x].getName() == start) { //find the starting node
            nodes[x].setVisited(1);
        }
        else {
            nodes[x].setVisited(0);
        }
    }
    vector<string> path;
    path.push_back(start);
    double total = 0;
    while(path.size() < num) {
        test = itr->second;
        double min = itr->second.getConnections()[0].getWeight();
        int index = 0;
        int index2;
        int counter = 0;
        for (int x = 0; x < nodes.size(); x++) {
            //find the minimun value to start with
            if (strcmp(nodes[x].getName().c_str(), test.getConnections()[counter].getName().c_str()) == 0) {
                if (nodes[x].getVisited() != 0) { //check if that node is already visited and in the stack
                    counter ++;
                    index = counter;
                    min = itr->second.getConnections()[counter].getWeight();
                    x = 0;
                }
                else {
                    index2 = x;
                }
            }
        }

        for(int x = 0; x < itr->second.getConnections().size(); x++) {
            if (itr->second.getConnections()[x].getWeight() < min) { //find the minimum weight
                bool check = false;
                for (int y = 0; y < nodes.size(); y++) {
                    //check if that node has already been visited
                    if (strcmp(nodes[y].getName().c_str(),itr->second.getConnections()[x].getName().c_str()) == 0 && nodes[y].getVisited() == 0) {
                        check = true;
                        index2 = y;
                    }
                }
                if (check == true) { //if it has not been visited, it becomes the new min
                    min = itr->second.getConnections()[x].getWeight();
                    index = x;
                }
            }
        }
        if (path.size() == num -1) { //if the size is 1 less than the target size, that means there is only one node left to visit, so this is a default
            path.push_back(itr->second.getConnections()[counter].getName().c_str());
            total += itr->second.getConnections()[counter].getWeight();
            itr = map.find(itr->second.getConnections()[counter].getName());
        }
        else {
            path.push_back(itr->second.getConnections()[index].getName().c_str()); //push back the node with the lowest weight

            nodes[index2].setVisited(1);
            total += itr->second.getConnections()[index].getWeight(); //add to the weight
            itr = map.find(itr->second.getConnections()[index].getName()); //get the next node
        }
    }

    test = itr->second;
    for (int x = 0; x < itr->second.getConnections().size(); x++) {
        if (strcmp(itr->second.getConnections()[x].getName().c_str(),start.c_str()) == 0) { //find the edge to the starting node
            total += itr->second.getConnections()[x].getWeight(); //add its weight
        }
    }

    cout << "NEAREST NEIGHBOR PATH + WEIGHT:" << endl;
    path.push_back(start.c_str());
    for (int x = 0; x < path.size(); x++) {
        cout << path[x] << endl;
    }
    cout << total << endl << endl;
}
