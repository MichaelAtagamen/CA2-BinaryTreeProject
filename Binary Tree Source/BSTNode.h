#pragma once
#include <iostream>

using namespace std;

template <class T>
class BSTNode {
    BSTNode<T>* parent;
    BSTNode<T>* left;
    BSTNode<T>* right;
    T data;

public:
    BSTNode();
    BSTNode(const BSTNode<T>& other);
    BSTNode<T>* operator=(const BSTNode<T>& other);
    BSTNode(T data);
    void setItem(T item);
    int count();
    void add(T& item);
    BSTNode<T>* getParent();
    BSTNode<T>* getLeft();
    BSTNode<T>* getRight();
    void setLeft(BSTNode<T>* l);
    void setRight(BSTNode<T>* r);
    T& getItem();
    ~BSTNode();
};

template <class T>
BSTNode<T>::BSTNode() : parent(nullptr), left(nullptr), right(nullptr) {}

template <class T>
BSTNode<T>::BSTNode(T data) : parent(nullptr), left(nullptr), right(nullptr), data(data) {}

template <class T>
BSTNode<T>::BSTNode(const BSTNode<T>& other) : parent(nullptr), left(nullptr), right(nullptr), data(other.data) {
    if (other.left) this->left = new BSTNode<T>(*other.left);
    if (other.right) this->right = new BSTNode<T>(*other.right);
}

template <class T>
BSTNode<T>* BSTNode<T>::operator=(const BSTNode<T>& other) {
    if (this == &other) return this;
    delete left;
    delete right;
    left = right = nullptr;
    data = other.data;
    if (other.left) left = new BSTNode<T>(*other.left);
    if (other.right) right = new BSTNode<T>(*other.right);
    return this;
}

template <class T>
BSTNode<T>::~BSTNode() {
    delete left;
    delete right;
}

template <class T>
void BSTNode<T>::setItem(T item) {
    data = item;
}

template <class T>
T& BSTNode<T>::getItem() {
    return data;
}

template <class T>
BSTNode<T>* BSTNode<T>::getLeft() {
    return left;
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight() {
    return right;
}

template <class T>
BSTNode<T>* BSTNode<T>::getParent() {
    return parent;
}

template <class T>
void BSTNode<T>::setLeft(BSTNode<T>* l) {
    left = l;
}

template <class T>
void BSTNode<T>::setRight(BSTNode<T>* r) {
    right = r;
}

template <class T>
int BSTNode<T>::count() {
    int c = 1;
    if (left) c += left->count();
    if (right) c += right->count();
    return c;
}

template <class T>
void BSTNode<T>::add(T& item) {
    if (item == data) return; // Updated to handle duplicates
    if (item < data) {
        if (!left) {
            left = new BSTNode<T>(item);
            left->parent = this;
        }
        else {
            left->add(item);
        }
    }
    else {
        if (!right) {
            right = new BSTNode<T>(item);
            right->parent = this;
        }
        else {
            right->add(item);
        }
    }
}
