#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>

struct Player {
    std::string name;
    std::string team;
    std::string position;
    int gamesPlayed;
    float pointsPerGame;
    float fieldGoalPercentage;
};

class NBAData {
private:
    std::vector<Player> players;

public:
    // Load data from a CSV file
    bool loadData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file!" << std::endl;
            return false;
        }

        std::string line;
        getline(file, line); // Skip header line

        while (getline(file, line)) {
            std::stringstream ss(line);
            Player p;
            std::string temp;

            getline(ss, p.name, ',');
            getline(ss, p.team, ',');
            getline(ss, p.position, ',');
            getline(ss, temp, ',');
            p.gamesPlayed = std::stoi(temp);
            getline(ss, temp, ',');
            p.pointsPerGame = std::stof(temp);
            getline(ss, temp, ',');
            p.fieldGoalPercentage = std::stof(temp);

            players.push_back(p);
        }

        file.close();
        return true;
    }

    // Create an index based on a field (team, position, etc.)
    void createIndex(const std::string& field) {
        std::unordered_map<std::string, int> index;

        for (const auto& player : players) {
            std::string key;
            if (field == "Team") {
                key = player.team;
            }
            else if (field == "Position") {
                key = player.position;
            }
            else {
                std::cout << "Invalid field for index." << std::endl;
                return;
            }
            index[key]++;
        }

        std::cout << "Index for " << field << ":" << std::endl;
        for (const auto& pair : index) {
            std::cout << pair.first << ": " << pair.second << " players" << std::endl;
        }
    }

    // Display data for a specific field value
    void displaySubset(const std::string& field, const std::string& value) {
        std::cout << "Displaying data for " << field << " = " << value << ":\n";

        for (const auto& player : players) {
            bool match = false;
            if (field == "Team" && player.team == value) {
                match = true;
            }
            else if (field == "Position" && player.position == value) {
                match = true;
            }

            if (match) {
                std::cout << "Name: " << player.name
                    << ", Team: " << player.team
                    << ", Position: " << player.position
                    << ", Games Played: " << player.gamesPlayed
                    << ", PPG: " << player.pointsPerGame
                    << ", FG%: " << player.fieldGoalPercentage
                    << std::endl;
            }
        }
    }
};

int main() {
    NBAData nbaData;

    // Load the NBA data from CSV file
    if (!nbaData.loadData("NBA_Player_Stats.csv")) {
        return 1; // If loading fails, exit
    }

    int choice;
    std::string field, value;

    while (true) {
        std::cout << "1. Create Index based on a field (Team/Position)\n";
        std::cout << "2. View data based on a field value\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline left in the buffer

        switch (choice) {
        case 1:
            std::cout << "Enter the field to index (Team/Position): ";
            std::getline(std::cin, field);
            nbaData.createIndex(field);
            break;
        case 2:
            std::cout << "Enter the field to search by (Team/Position): ";
            std::getline(std::cin, field);
            std::cout << "Enter the value for " << field << ": ";
            std::getline(std::cin, value);
            nbaData.displaySubset(field, value);
            break;
        case 3:
            std::cout << "Exiting the program.\n";
            return 0;
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
