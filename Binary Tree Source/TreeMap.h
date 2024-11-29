#pragma once
#include "BinaryTree.h"
#include <utility>

template <typename K, typename V>
class TreeMap {
private:
    BinaryTree<std::pair<K, V>> tree;

public:
    void put(const K& key, const V& value) {
        tree.add(std::make_pair(key, value));
    }

    bool containsKey(const K& key) {
        return tree.contains(std::make_pair(key, V()));
    }

    void clear() { tree.clear(); }

    void printKeys() const { tree.printInOrder(); }
};
