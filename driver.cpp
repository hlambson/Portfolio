//
// Created by henry on 4/14/2020.
//

#include "driver.h"
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;

driver::driver() {

}

void driver::readIn(char * q) {
    ifstream file;
    file.open(q);
    if (!file.is_open()) {
        cout << "graph file didnt open" << endl;
        exit(-1);
    }

    int rows;
    char* buffer = new char[5];
    file.getline(buffer,5);
    rows = atoi(buffer);
    int counter = 0;
    string val1;
    string val2;
    int weight;
    int check = 0;
    //read in the graphs from the files
    while(counter < rows) {
        getline(file,val1,',');
        getline(file,val2,',');
        file.getline(buffer,5);
        weight = atoi(buffer);
        edge temp(val1,val2);
        edge temp2(val2,val1);
        temp.setWeight(weight);
        //initial push of the data
        if (check == 0) {
            set1.makeSet(val1);
            set1.makeSet(val2);
            set2.makeSet(val1);
            set2.makeSet(val2);
            edges.push_back(temp);
            check = 1;
        }
        else {
            //pushing the rest of the data
            int check2 = 0;
            int check3 = 0;
            for (int x = 0; x < edges.size(); x++) {
                if (edges[x].getName1() == val1 || edges[x].getName2() == val1) { //check if the value is already in the disjoint set
                    check2 = 1;
                }
                if (edges[x].getName1() == val2 || edges[x].getName2() == val2) { //same
                    check3 = 1;
                }
            }
            if (check2 == 0) { //if the value is not in the sets, add it
                set2.makeSet(val1);
                set1.makeSet(val1);
            }
            if (check3 == 0) { //same
                set2.makeSet(val2);
                set1.makeSet(val2);
            }
            edges.push_back(temp); //push back the edge into the edge vector
        }
        counter++;
    }
}

void driver::kruskalsModified(char* out) {
    sort(edges.begin(), edges.end()); //sort edges by their weights
    minEdges.clear();
    string val1 = edges[0].getName1(); //get the first edge
    string val2 = edges[0].getName2();
    set2.makeUnion(val1,val2); //make a union with the first values
    minEdges.push_back(edges[0]); //push back used edge onto the minEdge vector
    for (int x = 1; x < edges.size(); x++) {
        bool check = false;
        string p1 = set2.find(edges[x].getName1()).getParent(); //get the parent of the root of value1's tree
        string p2 = set2.find(edges[x].getName2()).getParent(); //get the parent of the root of value2's tree
            if (p1== p2) { //if the parents are equal, they are in the same tree, so dont make a union out of them
                check = true;
            }

        if (check == false) { //if they are not equal, make union
            set2.makeUnion(edges[x].getName1(), edges[x].getName2());
            minEdges.push_back(edges[x]);
        }
    }

    ofstream output;
    output.open(out);
    //print to file
    if (!output.is_open()) {
        cout << "output file didnt open" << endl;
    }
    double sum = 0;
    output <<"OUTPUT FROM MODIFIED DISJOINT SET" << endl;
    for (int x = 0;  x < minEdges.size(); x++) {
        output << minEdges[x].getName1() << " - " << minEdges[x].getName2() << endl;
        sum += minEdges[x].getWeight();
    }

    output << "Total Weight: " << sum << endl << endl;

}

void driver::kruskalsTrivial(char * out) {
    //the logic here is the same as the modified version, this one just uses the trivial disjoint set
    sort(edges.begin(), edges.end());
    minEdges.clear();
    string val1 = edges[0].getName1();
    string val2 = edges[0].getName2();
    set1.makeUnion(val1,val2);
    minEdges.push_back(edges[0]);
    for (int x = 1; x < edges.size(); x++) {
        bool check = false;
        string p1 = *set1.find(edges[x].getName1()).begin();
        string p2 = *set1.find(edges[x].getName2()).begin();
        if (p1 == p2) {
            check = true;
        }

        if (check == false) {
            set1.makeUnion(edges[x].getName1(), edges[x].getName2());
            minEdges.push_back(edges[x]);
        }
    }

    ofstream output;
    output.open(out,ios_base::app);
    if (!output.is_open()) {
        cout << "output file didnt open" << endl;
        exit(-1);
    }
    double sum = 0;
    output <<"OUTPUT FROM TRIVIAL DISJOINT SET" << endl;
    for (int x = 0;  x < minEdges.size(); x++) {
        output << minEdges[x].getName1() << " - " << minEdges[x].getName2() << endl;
        sum += minEdges[x].getWeight();
    }

    output << "Total Weight: " << sum << endl;

    edges.clear();
    minEdges.clear();
}