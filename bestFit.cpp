//
// Created by henry on 2/4/2020.
//

#include "bestFit.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;
//This is an algorithm for allocating memory at the location that fits it best that I wrote for a program in my Algorithms class.
//The program was to create a custom memory manager using different strategies of allocation, one of them being best fit

//The book variable is a vector of objects that keeps track of what memory has already been allocated 
//The objects in the vector have void* of what is allocated's initial and final memory address


bestFit::bestFit() {}

void* bestFit::giveMem(size_t a) {
    if (book.empty()) { //if the bookkeeping vector is empty, store at the first location
        storage temp;
        temp.setInit(initial);
        temp.setSize(a);
        void* test = temp.getInit();
        char* tempPtr = (char*)test + a;
        temp.setFin(tempPtr);
        book.push_back(temp);
        return initial;
    }
    else {
        size_t closest;
        void* tempLocation;
        char* ptr = static_cast<char *>(initial);
        char* ptr2 = static_cast<char *>(book[0].getInit());
        char* finalPtr = static_cast<char *>(final);
        tempLocation = initial;
        closest = ptr2 - ptr; //check the position between the initial pointer and the first item in the vector

        for (int x = 0; x < book.size(); x++) {
            ptr = static_cast<char *>(book[x].getFin());
            ptr2 = static_cast<char *>(book[x + 1].getInit());

            size_t num = ptr2 - ptr;
            if ((x + 1) == book.size()) { //if we are at the end of the vector
                if (finalPtr - ptr < a) {  //check if there is enough space left in the memory to store
                    cout << "Error, no room to store" << endl;
                    return nullptr;
                }
                else {
                    if (closest > a) { //if the end of the loop gets reached and there is a viable spot add it
                        storage temp;
                        char* fin = static_cast<char *>(tempLocation) + 1;
                        tempLocation = fin;
                        temp.setInit(fin);
                        temp.setSize(a);
                        char* tempPtr = static_cast<char *>(tempLocation);
                        tempPtr += a ;
                        temp.setFin(tempPtr);
                        book.push_back(temp);
                        sort(book.begin(),book.end());
                        return tempLocation;
                    }
                    tempLocation = book[x].getFin();
                    storage temp;
                    char* fin = static_cast<char *>(tempLocation) + 1;
                    tempLocation = fin;
                    temp.setInit(fin);
                    temp.setSize(a);
                    char* tempPtr = static_cast<char *>(tempLocation);
                    tempPtr += a ;
                    temp.setFin(tempPtr);
                    book.push_back(temp);
                    sort(book.begin(),book.end());
                    return tempLocation;
                }
            }
            if (a - closest < 0) { //check if there is enough space to store
                closest = num;
                tempLocation = book[x].getFin();
            }
            else {
                if (num > a && (closest - a) > (num - a)) { //if the next interval is bigger than the target and closer than the current closest, set it as the new closest
                    closest = num;
                    tempLocation = book[x].getFin();
                }
            }
        } //end for

    }
    return nullptr; //this should never happen
}

//method to deallocate memory, essentially just removes it from the vector to be written over later
void bestFit::takeMem(void * ptr) {
    for (int x = 0; x < book.size(); x++) {
        if (book[x].getInit() == ptr) {
            book.erase(book.begin() + x);
        }
    }
}

