#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "NBA.h"
#include "TreeMap.h"

using namespace std;

// Function to load data from CSV file and create Player objects
vector<Player> loadPlayersFromCSV(const string& filename) {
    ifstream file(filename);
    vector<Player> players;
    string line, name, team, position;
    int gamesPlayed;
    float pointsPerGame, fieldGoalPercentage;

    if (file.is_open()) {
        getline(file, line); // Skip the header line

        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, team, ',');
            getline(ss, position, ',');
            ss >> gamesPlayed;
            ss.ignore();
            ss >> pointsPerGame;
            ss.ignore();
            ss >> fieldGoalPercentage;

            players.push_back(Player(name, team, position, gamesPlayed, pointsPerGame, fieldGoalPercentage));
        }
        file.close();
    }
    return players;
}

// Function to create an index for a specified field
void createIndex(TreeMap<string, Player>& treeMap, const vector<Player>& players, const string& field) {
    for (const auto& player : players) {
        if (field == "Player") {
            treeMap.put(player.name, player);
        }
        else if (field == "Team") {
            treeMap.put(player.team, player);
        }
        else if (field == "Position") {
            treeMap.put(player.position, player);
        }
    }
}

// Function to search and display data based on a given field
void searchAndDisplayData(TreeMap<string, Player>& treeMap, const string& field) {
    string key;
    cout << "Enter " << field << " to search for: ";
    cin >> key;
    try {
        Player player = treeMap.get(key);
        cout << "Found " << field << " data:\n";
        cout << player.name << ", " << player.team << ", " << player.position << ", "
            << player.gamesPlayed << ", " << player.pointsPerGame << ", "
            << player.fieldGoalPercentage << "%\n";
    }
    catch (const std::logic_error&) {
        cout << "No data found for " << key << ".\n";
    }
}

int main() {
    string filename = "NBA_Player_Stats.csv";
    vector<Player> players = loadPlayersFromCSV(filename);

    TreeMap<string, Player> playerIndex, teamIndex, positionIndex;

    // Index players by their fields
    createIndex(playerIndex, players, "Player");
    createIndex(teamIndex, players, "Team");
    createIndex(positionIndex, players, "Position");

    int choice;
    while (true) {
        cout << "\nNBA Player Stats Search Menu\n";
        cout << "1. View index of players\n";
        cout << "2. View index of teams\n";
        cout << "3. View index of positions\n";
        cout << "4. Search by Player\n";
        cout << "5. Search by Team\n";
        cout << "6. Search by Position\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            playerIndex.keySet().print(); // Print all player names
            break;
        case 2:
            teamIndex.keySet().print(); // Print all team names
            break;
        case 3:
            positionIndex.keySet().print(); // Print all positions
            break;
        case 4:
            searchAndDisplayData(playerIndex, "Player");
            break;
        case 5:
            searchAndDisplayData(teamIndex, "Team");
            break;
        case 6:
            searchAndDisplayData(positionIndex, "Position");
            break;
        case 0:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}
