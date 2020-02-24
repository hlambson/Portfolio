#include "dsstring.h"
#include <iostream>
#include <cstring>
//custom string class made for my Data Structures class


using namespace std;

//default contructor
DSString::DSString() {
    data = nullptr;
    length = 0;
}

//contructor that takes a char*
DSString::DSString(const char* d) {
   length = strlen(d);
    data = new char[length + 1];

    strcpy(data,d);
}

//copy constructor
DSString::DSString(const DSString& d) {
   length = strlen(d.data);
    data = new char[length + 1];
    strcpy(data,d.data);
}

//destructor
DSString::~DSString() {
    delete[] data;
}

//overloaded assignment with char*
DSString& DSString::operator= (const char* d) {
    length = strlen(d);
    if (data != nullptr) {
        delete[] data;
    }
    this->data = new char[length + 1];                          //allowcate new memory for the new length of the string
    strcpy(data,d);                                                //copy the new string into data
    return *this;                                                  //return the new string
}

//overloaded assignment with DSString
DSString& DSString::operator=(const DSString& p) {
    length = strlen(p.data);
    this->data = new char[length + 1];                     //allowcate new memory for the new length of the string
    strcpy(this->data,p.data);                                     //copy the new string into data
    return *this;                                                  //return the new string
}

//overloaded +
DSString DSString::operator+(const DSString& p) {

    length += strlen(p.data);
    strcat(this->data,p.data);
    return *this;
}

//overloaded +=
DSString& DSString::operator+=(const DSString& p) {
    char* temp = this->data;
    int tempLength = strlen(temp);
    length = strlen(p.data);
    this->data = new char[tempLength + length + 1];         //create new space to store the concatenated string
    strcpy(this->data,temp);                                        //copy the old string to the new location
    strcat(this->data,p.data);                                      //concatenate the two strings together
    delete temp;                                                    //delete space used for the original string
    return *this;
}

//overloaded == with char*
bool DSString::operator== (const char* p) {
    if (strcmp(this->data,p) == 0) {
        return true;
    }
    else {
        return false;
    }
}

//overloaded == with DSString
bool DSString::operator== (const DSString& p) {
    if (strcmp(this->data,p.data) == 0) {
        return true;
    }
    else {
        return false;
    }
}

//overloaded < with char*
bool DSString::operator< (const char* p) {
    if (strcmp(this->data,p) < 0) {
        return true;
    }
    else {
        return false;
    }
}

//overloaded < with DSString
bool DSString::operator< (const DSString& p) {
    if (strcmp(this->data,p.data) < 0) {
        return true;
    }
    else {
        return false;
    }
}

//overloaded index
char& DSString::operator[] (const int num) {
    return this->data[num];
}


int DSString::size() {
    return length;
}

//substring function
DSString DSString::substring(int a, int b) {
  char* temp;
  int size = b;
  size = abs(size);  //find the size of the substring
  temp = new char[size + 1];

  int y = 0;
  if (b > 0) {

      for (int x = 0; x < b; x++) {
            temp[y] += data[a + x];                                 //iterate through and add on the characters going to the right
            y++;
      }
      temp[size] = '\0';
  }
  y = 0;
  if (b < 0) {
      for (int z = 0; y > b && temp[y] != '\0'; z--) {
          temp[y] += data[a + z];                                 //iterate through and add on the characters going to the left
          y++;
      }
      temp[size] = '\0';
 }
  DSString sub = DSString(temp);
  return sub;

}

//to c_str
char* DSString::c_str() {
        return this->data;
}

//overloaded << operator
std::ostream& operator<< (std::ostream& stream, const DSString& d) {
    for (int x = 0; x < d.length; x++) {
   stream << d.data[x];
}
    return stream;

}
