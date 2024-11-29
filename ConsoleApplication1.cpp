#include <iostream>
#include <fstream>
#include <cctype> // For std::tolower
#include <string>
#include "TreeMap.h" // Your TreeMap implementation
#include "BinaryTree.h" // Assuming you have a BinaryTree class

void loadWordsFromFile(const std::string& filename, TreeMap<char, BinaryTree<std::string>>& letterMap) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        if (!word.empty()) {
            char firstLetter = std::tolower(word[0]); // Ensure case insensitivity
            if (std::isalpha(firstLetter)) { // Only process alphabetic characters
                if (!letterMap.containsKey(firstLetter)) {
                    letterMap.put(firstLetter, BinaryTree<std::string>()); // Create a new BinaryTree for the letter
                }
                letterMap.get(firstLetter).add(word); // Add the word to the BinaryTree for the letter
            }
        }
    }
}

void displayWordsForLetter(const TreeMap<char, BinaryTree<std::string>>& letterMap, char letter) {
    if (letterMap.containsKey(letter)) {
        const BinaryTree<std::string>& wordsTree = letterMap.get(letter);
        auto wordsArray = wordsTree.toArray(); // Assuming you have a toArray() method in BinaryTree
        int wordCount = wordsTree.count(); // Number of words
        if (wordCount > 0) {
            std::cout << "Words under letter '" << letter << "':" << std::endl;
            for (int i = 0; i < wordCount; ++i) {
                std::cout << wordsArray[i] << std::endl;
            }
            delete[] wordsArray; // Clean up dynamic array
        }
        else {
            std::cout << "No words found for the letter: " << letter << std::endl;
        }
    }
    else {
        std::cout << "No words found for the letter: " << letter << std::endl;
    }
}

int main() {
    TreeMap<char, BinaryTree<std::string>> letterMap;
    std::string filename = "sample_text.txt";

    // Load words from the file into the TreeMap
    loadWordsFromFile(filename, letterMap);

    // Display available letters in the map
    std::cout << "\nLetters in the map:" << std::endl;
    auto keysTree = letterMap.keySet();
    auto keysArray = keysTree.toArray(); // Assuming keySet() returns a BinaryTree<char>
    int keyCount = keysTree.count(); // Number of keys
    for (int i = 0; i < keyCount; ++i) {
        std::cout << keysArray[i] << " ";
    }
    delete[] keysArray; // Clean up dynamic array
    std::cout << "\n";

    // Allow user to search for words by letter
    char inputLetter;
    while (true) {
        std::cout << "\nEnter a letter to display words (or '0' to quit): ";
        std::cin >> inputLetter;

        if (inputLetter == '0') {
            break;
        }

        inputLetter = std::tolower(inputLetter); // Convert input to lowercase for consistency
        if (std::isalpha(inputLetter)) {
            displayWordsForLetter(letterMap, inputLetter);
        }
        else {
            std::cout << "Invalid input. Please enter a letter or '0' to quit." << std::endl;
        }
    }

    return 0;
}
