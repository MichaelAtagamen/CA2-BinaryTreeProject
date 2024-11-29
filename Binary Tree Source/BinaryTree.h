#pragma once
#include "BSTNode.h"
#include <vector>
#include <iostream>
#include <stdexcept>

template <class T>
class BinaryTree {
private:
    void addItemToArray(const BSTNode<T>* node, int& pos, T* arr) const;  // Make this function const-qualified
    void printInOrder(BSTNode<T>* node);
    void printPreOrder(BSTNode<T>* node);
    void printPostOrder(BSTNode<T>* node);

public:
    BSTNode<T>* root;

    // Constructors and Destructor
    BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree<T>& operator=(const BinaryTree<T>& other);
    ~BinaryTree();

    // Core Operations
    void add(const T& item);
    bool remove(const T& item);
    const T& get(const T& item) const;  // Modified to return const T&
    void clear();

    // Utility Functions
    int count() const;
    T* toArray() const;
    void printInOrder();
    void printPreOrder();
    void printPostOrder();

    // Comparison Operators
    bool operator<(const BinaryTree<T>& other) const;
    bool operator==(const BinaryTree<T>& other) const;
};

// Implementations

template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) : root(nullptr) {
    if (other.root) {
        root = new BSTNode<T>(*other.root);
    }
}

template <class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other) {
    if (this != &other) {
        clear();
        if (other.root) {
            root = new BSTNode<T>(*other.root);
        }
    }
    return *this;
}

template <class T>
BinaryTree<T>::~BinaryTree() {
    clear();
}

template <class T>
void BinaryTree<T>::add(const T& item) {
    if (!root) {
        root = new BSTNode<T>(item);
    }
    else {
        root->add(item);
    }
}

template <class T>
bool BinaryTree<T>::remove(const T& item) {
    BSTNode<T>* parent = nullptr;
    BSTNode<T>* current = root;

    while (current && current->getItem() != item) {
        parent = current;
        current = (item < current->getItem()) ? current->getLeft() : current->getRight();
    }

    if (!current) return false;

    if (!current->getLeft() || !current->getRight()) {
        BSTNode<T>* replacement = current->getLeft() ? current->getLeft() : current->getRight();
        if (!parent) {
            root = replacement;
        }
        else if (parent->getLeft() == current) {
            parent->setLeft(replacement);
        }
        else {
            parent->setRight(replacement);
        }
        delete current;
        return true;
    }

    BSTNode<T>* successorParent = current;
    BSTNode<T>* successor = current->getRight();
    while (successor->getLeft()) {
        successorParent = successor;
        successor = successor->getLeft();
    }

    current->setItem(successor->getItem());
    if (successorParent->getLeft() == successor) {
        successorParent->setLeft(successor->getRight());
    }
    else {
        successorParent->setRight(successor->getRight());
    }
    delete successor;
    return true;
}

template <class T>
const T& BinaryTree<T>::get(const T& item) const {
    BSTNode<T>* current = root;
    while (current) {
        if (item == current->getItem()) {
            return current->getItem();
        }
        current = (item < current->getItem()) ? current->getLeft() : current->getRight();
    }
    throw std::logic_error("Item not found");
}

template <class T>
void BinaryTree<T>::clear() {
    delete root;
    root = nullptr;
}

template <class T>
int BinaryTree<T>::count() const {
    return root ? root->count() : 0;
}

template <class T>
T* BinaryTree<T>::toArray() const {
    int totalNodes = count();
    T* arr = new T[totalNodes];
    int pos = 0;
    addItemToArray(root, pos, arr);  // Calling the const version of addItemToArray
    return arr;
}

template <class T>
void BinaryTree<T>::addItemToArray(const BSTNode<T>* node, int& pos, T* arr) const {
    if (node) {
        addItemToArray(node->getLeft(), pos, arr);
        arr[pos++] = node->getItem();
        addItemToArray(node->getRight(), pos, arr);
    }
}

template <class T>
void BinaryTree<T>::printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printInOrder(BSTNode<T>* node) {
    if (node) {
        printInOrder(node->getLeft());
        std::cout << node->getItem() << " ";
        printInOrder(node->getRight());
    }
}

template <class T>
void BinaryTree<T>::printPreOrder() {
    printPreOrder(root);
    std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPreOrder(BSTNode<T>* node) {
    if (node) {
        std::cout << node->getItem() << " ";
        printPreOrder(node->getLeft());
        printPreOrder(node->getRight());
    }
}

template <class T>
void BinaryTree<T>::printPostOrder() {
    printPostOrder(root);
    std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::printPostOrder(BSTNode<T>* node) {
    if (node) {
        printPostOrder(node->getLeft());
        printPostOrder(node->getRight());
        std::cout << node->getItem() << " ";
    }
}

template <class T>
bool BinaryTree<T>::operator<(const BinaryTree<T>& other) const {
    return this->count() < other.count();
}

template <class T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& other) const {
    return this->count() == other.count();
}
