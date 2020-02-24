#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include "avlnode.h"
//custom AVL Tree class written for Data Structures
//used in a search engine program to store documents

using namespace std;

template <typename T>
class AVL{
    public:
        //default constructor
        AVL(){
            root=nullptr;
        }
        
        //root node and getter for root
        AVLNode<T> *root;
        AVLNode<T>*& getRoot() {
            return root;
        }
      
    
    AVL(const AVL &rhs):
        root(nullptr){
        *this =rhs;
    }
    
    //destructor and make empty function
    ~AVL(){makeEmpty();}
    
    void makeEmpty(){
        makeEmpty(root);
    }
    
    void makeEmpty(AVLNode<T>* node) {
        if (node != nullptr) { //recurse through the tree and delete every node
            makeEmpty(node->left);
            makeEmpty(node->right);
            delete node;
        }
    }
    
    //check if the tree contains a specific node
    bool contains(T x, AVLNode<T>* node) {
        if (node != nullptr) {
            if (x < root->getElement()) {
                return search(x,node->left);
            }
            else if (x > root->getElement()) {
                return search(x,node->right);
            }
            else {
                return true;
            }
        }
        else {
            return false;
        }
    }
    
    //return a specific node in the tree
     AVLNode<T>* search(T& x) {
        search(x,this->root);
    }
    
    AVLNode<T>* search(T& x,AVLNode<T>* node){
        if (node != nullptr) {
            if (x < node->getElement()) {
                return search(x,node->left);
            }
            else if (x > node->getElement()) {
                return search(x,node->right);
            }
            else {
                return node;
            }
        }
        else {
            return nullptr;
        }

    }
    
    //check if the tree is empty
    bool isEmpty() const{
        return root ==  nullptr;
    }
    
    //return the height of the tree
    int height(AVLNode<T> *t) const{
        return t == nullptr? -1 : t ->height;
    }
    
    //return the maximum height
    int max (int lhs, int rhs)  const{
        return lhs > rhs ? lhs:rhs;
    }
    
    //rotation functions for balacing the tree
    
    //single rotate left
    void rotateWithLeftChild(AVLNode<T>* &k2) {
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), (k2->height)) + 1;
        k2 = k1;
    }
    
    //double rotate left
    void doubleWithleftChild(AVLNode<T> * & k3){

        rotateWithRightchild(k3->left);
        rotateWithLeftChild(k3);
    }
    
    //single rotate right
    void rotateWithRightchild(AVLNode<T>* &k2) {
        AVLNode<T>* k1 = k2->right;
        k2->right  = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;

    }
    
    //double rotate right
    void doubleWithRightChild(AVLNode<T> * k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightchild(k3);
    }

    
    //insert into the tree 
    void insert( T  x){
        insert(x, root);
    }
    
    void insert(T &x, AVLNode<T>* &t) {
        if (t==nullptr) {
            t = new AVLNode<T>(x,NULL,NULL);
        }
        else if(x < t->element) {
            insert(x,t->left);
            if(height(t->left) - height(t->right)  > 1) {
                if (x < t->left->element) {
                    rotateWithLeftChild(t);
                }
                else {
                    doubleWithleftChild(t);
                }

            }

        }
        else if (t->element < x) {
            insert(x,t->right);
            if ((height(t->right)) - (height(t->left)) > 1) {
                if (x > t->right->element) {
                    rotateWithRightchild(t);
                }
                else {
                        doubleWithRightChild(t);
                }
           }
       }

        t->height = max(height(t->left), height(t->right)) + 1;
    }






};




#endif // AVL_H
