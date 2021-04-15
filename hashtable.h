#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <avl.h>
#include <functional>

#ifndef HASHTABLE_H
#define HASHTABLE_H
//custom hashtable using my custom AVL tree class 


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

//default constructor
template<typename T, typename U>
HashTable<T,U>::HashTable(){

}

//destuctor, just lets AVL destructor delete everything
template<typename T, typename U>
HashTable<T,U>::~HashTable(){

}

//find where to insert using hash function and insert into the table
template<typename T, typename U>
void HashTable<T,U>::insertHash(T x, U y) {
    hash<U>temp2; //hash and insert at the location
    int index = temp2(y) % htsize;
    arr[index].insert(x); //calls the AVL tree insert function

}

//search for a node
template <typename T,typename U>
T& HashTable<T,U>::find(T& x)  {
    hash<T> temp;

   int index = temp(x) % htsize;
    AVLNode<T>* node = arr[index].search(x);
    return node->getElement();
}

//return the size of the table
template <typename T,typename U>
int HashTable<T,U>::getSize() {
    return htsize;
}

//returns the table
template <typename T, typename U>
AVL<T>* HashTable<T,U>::getArr() {
    return arr;
}

//make empty function
template<typename T, typename U>
void HashTable<T,U>::makeEmpty(){

    for(int i = 0; i <htsize;i++){
        arr[i].makeEmpty(); //calls the AVL tree make empty funciton for every tree in the table

    }
}













#endif // HASHTABLE_H
