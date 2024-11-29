#pragma once
#include "BinaryTree.h"
#include <stdexcept>

template <typename K, typename V>
class TreeMap {
private:
    BinaryTree<std::pair<K, V>> tree; // Stores key-value pairs in a BinaryTree

public:
    // Clears all elements from the TreeMap
    void clear() {
        tree.clear();
    }

    // Checks if the TreeMap contains the specified key
    bool containsKey(const K& key) const {
        try {
            get(key); // Attempt to find the key
            return true;
        }
        catch (const std::logic_error&) {
            return false;
        }
    }

    // Retrieves the value associated with the specified key
    V get(const K& key) const {
        std::pair<K, V> searchPair(key, V()); // Create a dummy pair for lookup
        return tree.get(searchPair).second;   // Return the value corresponding to the key
    }

    // Adds or updates a key-value pair in the TreeMap
    void put(const K& key, const V& value) {
        std::pair<K, V> newPair(key, value);
        if (containsKey(key)) {
            tree.remove(newPair); // Remove the existing pair
        }
        tree.add(newPair); // Add the new pair
    }

    // Retrieves all keys in the TreeMap as a BinaryTree
    BinaryTree<K> keySet() {
        BinaryTree<K> keys;
        auto allPairs = tree.toArray(); // Get all key-value pairs
        for (int i = 0; i < tree.count(); ++i) {
            keys.add(allPairs[i].first); // Extract and add the keys
        }
        delete[] allPairs; // Clean up the dynamic array
        return keys;
    }

    // Returns the number of key-value pairs in the TreeMap
    int size() {
        return tree.count();
    }

    // Removes the key-value pair with the specified key
    bool removeKey(const K& key) {
        if (!containsKey(key)) {
            return false;
        }
        std::pair<K, V> removePair(key, V());
        return tree.remove(removePair);
    }

    // Provides array-style access to values in the TreeMap
    V& operator[](const K& key) {
        return get(key);
    }
};
