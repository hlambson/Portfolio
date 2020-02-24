#ifndef DLLIST_H
#define DLLIST_H
#include "listnode.h"
template <typename T>
class DLList {
private:

    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* current;
    int size;
public:
    DLList();
    DLList(const T);
    DLList(const DLList<T>&);
    DLList& operator=(const DLList);
    ~DLList();

    ListNode<T>* getNext();
    ListNode<T>* getCurrent();
    ListNode<T>* searchingIterator(int);
    ListNode<T>* getHead();
    ListNode<T>* getTail();
    void incCurrent();
    void resetCurrent();
    int getSize();

    void push_front(const T);
    void pop_front();
    void push_back(const T);
    void pop_back();

};

//default constructor
template <typename T>
DLList<T>::DLList() {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    size = 0;
}

//constructor that takes a data type as a parameter
template <typename T>
DLList<T>::DLList(const T x) {

    head = new ListNode<T>(x);
    tail = head;
    current = head;
    size = 1;
}

//copy constructor
template <typename T>
DLList<T>::DLList(const DLList<T>& c) {
   head = new ListNode<T>(c.head->data);
   current = head;
   size = c.size;
   while (current->next != nullptr) {
       current->next = new ListNode<T>(current->next->data);
       current = current->next;
   }
   this->tail = current;
}

//overloaded assignment
template<typename T>
DLList<T>& DLList<T>::operator=(const DLList c) {
    head = new ListNode<T>(c.head->data);
    current = head;
    size = c.size;
     ListNode<T>* tempIterator = c.head;
    while (tempIterator->next != nullptr) {
        current->next = new ListNode<T>(tempIterator->next->data);
        tempIterator = tempIterator->next;
        current = current->next;
    }
    this->tail = current;
}

//destructor
template<typename T>
DLList<T>::~DLList<T>() {
    ListNode<T>* current = head;
    while (current != nullptr) {
        current = current->next;
        delete head;
        head = current;
    }
}

//return current node
template <typename T>
ListNode<T>* DLList<T>::getCurrent() {
    return current;
}

template <typename T>
ListNode<T>* DLList<T>::searchingIterator(int index) {
    ListNode<T>* tempIterator = head;
    int counter = 0;
    while (counter != index) {
        tempIterator = tempIterator->next;
        counter ++;
    }
    return tempIterator;
}

//return head node
template <typename T>
ListNode<T>* DLList<T>::getHead() {
    return head;
}

//return tail node
template <typename T>
ListNode<T>* DLList<T>::getTail() {
    return tail;
}

//return the next node in the list
template <typename T>
ListNode<T>* DLList<T>::getNext() {
    return current->next;
}

//iterate current to the next node
template <typename T>
void DLList<T>::incCurrent() {
    current = current->next;
}

//put current back to head
template <typename T>
void DLList<T>::resetCurrent() {
    current = head;
}

//add a node to the fron of the list
template <typename T>
void DLList<T>::push_front(const T x) {
    if (head == nullptr) {
        head = new ListNode<T>(x);
        tail = head;
        size = 1;
    }
    else {
        head->previous = new ListNode<T>(x);
        head->previous->next = head;
        head = head->previous;
        size++;
    }
}

//remove the first node in the list
template <typename T>
void DLList<T>::pop_front() {
    if (size == 1) {
     //prevent seg faults
    }
    else {
    head = head->next;
    delete head->previous;
    head->previous = nullptr;
    size--;
    }
}

//push a node back to the end of the list
template <typename T>
void DLList<T>::push_back(const T x) {
    if (tail == nullptr) {
        tail = new ListNode<T>(x);
        head = tail;
        current = tail;
        size = 1;
    }
    else {
        tail->next = new ListNode<T>(x);
        tail->next->previous = tail;
        tail = tail->next;
        size++;
    }
}

//remove the last node in the list
template <typename T>
void DLList<T>::pop_back() {
    if (size == 1) {
     //prevent seg faults
    }
    else {
    tail = tail->previous;
    delete tail->next;
    tail->next = nullptr;
    size--;
    }
}

template <typename T>
int DLList<T>::getSize() {
    return size;
}


#endif // DLLIST_H
