#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include "avlnode.h"


using namespace std;

template <typename T>
class AVL{
    public:

        AVLNode<T> *root;
        AVLNode<T>*& getRoot() {
            return root;
        }
        AVL(){
            root=nullptr;
        }

    AVL(const AVL &rhs):
        root(nullptr){
        *this =rhs;
    }

    ~AVL(){makeEmpty();}

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

    const int & findMin() const{
        if(isEmpty())
        throw underflow_error("underflow");
        return findMin(root)->element;
    }

    const int & findMax() const
    {
        if(isEmpty())
            throw underflow_error("underflow");
        return findMax(root)->element;
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

    AVLNode<T>* search(T& x) {
        search(x,this->root);
    }
    

    bool isEmpty() const{
        return root ==  nullptr;
    }

    void makeEmpty(){
        makeEmpty(root);
    }

    void makeEmpty(AVLNode<T>* node) {
        if (node != nullptr) {
            makeEmpty(node->left);
            makeEmpty(node->right);
            delete node;
        }
    }
    void insert( T  x){
        /*if (this == nullptr) {
            AVL<T>* t = new AVL<T>();
            insert(x, t->root);
        }
        else {*/
        insert(x, root);
       // }
    }

    int height(AVLNode<T> *t) const{
        return t == nullptr? -1 : t ->height;
    }
    int max (int lhs, int rhs)  const{
        return lhs > rhs ? lhs:rhs;
    }



    void rotateWithLeftChild(AVLNode<T>* &k2) {
        AVLNode<T>* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), (k2->height)) + 1;
        k2 = k1;
    }

    void doubleWithleftChild(AVLNode<T> * & k3){

        rotateWithRightchild(k3->left);
        rotateWithLeftChild(k3);
    }

    void rotateWithRightchild(AVLNode<T>* &k2) {
        AVLNode<T>* k1 = k2->right;
        k2->right  = k1->left;
        k1->left = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;

    }

    void doubleWithRightChild(AVLNode<T> * k3) {
        rotateWithLeftChild(k3->right);
        rotateWithRightchild(k3);
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
            //cout << ((height(t->right) - (height(t->left))))<<endl;
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
