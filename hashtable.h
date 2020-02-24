#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <avl.h>
#include <functional>

#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

template<typename T, typename U>
class HashTable
{
public:
    HashTable();
   ~HashTable();
    void insertHash(T,U);
    T& find(T&);
    int getSize();
    AVL<T>* getArr();
    void  makeEmpty();


private:
    static const int htsize = 100;
    AVL<T> arr[htsize]; //hash table is an array of AVL trees

};

template<typename T, typename U>
HashTable<T,U>::HashTable(){

}
template<typename T, typename U>
HashTable<T,U>::~HashTable(){

}

template<typename T, typename U>
void HashTable<T,U>::insertHash(T x, U y) {
    hash<U>temp2; //hash and insert at the location
    int index = temp2(y) % htsize;
    arr[index].insert(x);

}

//search for a node
template <typename T,typename U>
T& HashTable<T,U>::find(T& x)  {
    hash<T> temp;

   int index = temp(x) % htsize;
    AVLNode<T>* node = arr[index].search(x);
    return node->getElement();
}

template <typename T,typename U>
int HashTable<T,U>::getSize() {
    return htsize;
}

template <typename T, typename U>
AVL<T>* HashTable<T,U>::getArr() {
    return arr;
}

template<typename T, typename U>
void HashTable<T,U>::makeEmpty(){

    for(int i = 0; i <htsize;i++){
        arr[i].makeEmpty();

    }
}













#endif // HASHTABLE_H
