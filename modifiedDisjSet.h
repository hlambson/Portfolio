//
// Created by henry on 4/13/2020.
//

#ifndef P3_MODIFIEDDISJSET_H
#define P3_MODIFIEDDISJSET_H
#include "node.h"
#include <unordered_map>
#include "superClass.h"
using namespace std;
template <typename T>
class modifiedDisjSet: public superClass<T> {
private:
    unordered_map<T,node<T>> disj;
public:
    modifiedDisjSet();
    void makeSet(T);
    node<T>& find(T);
    void makeUnion(T,T);
};

template <typename T>
modifiedDisjSet<T>::modifiedDisjSet() {

}

template <typename T>
void modifiedDisjSet<T>::makeSet(T x) { //make a new set in the structure
    node<T> temp(x);
    pair<T,node<T>> y(x,temp);
    disj.insert(y);
}

template <typename T>
node<T>& modifiedDisjSet<T>::find(T x) { //compress the tress by find returning the root
    if (disj.find(x)->second.getParent() == x) {
        return disj.find(x)->second;
    }
    else {
        return find(disj.find(x)->second.getParent());
    }
}

template <typename T>
void modifiedDisjSet<T>::makeUnion(T x, T y) {
    find(y).setParent(find(x).getValue()); //sets the parent of the root of y to be the root of x
}
#endif //P3_MODIFIEDDISJSET_H
