#pragma once

#include <string>

// Structure to hold player data
struct Player {
    std::string name;
    std::string team;
    std::string position;
    int gamesPlayed;
    float pointsPerGame;
    float fieldGoalPercentage;

    // Constructor to easily create Player objects
    Player(const std::string& n, const std::string& t, const std::string& p, int g, float pp, float fg)
        : name(n), team(t), position(p), gamesPlayed(g), pointsPerGame(pp), fieldGoalPercentage(fg) {}

    // Overload < operator for sorting/comparison based on player name
    bool operator<(const Player& other) const {
        return name < other.name;
    }

    // Overload == operator for comparing player names
    bool operator==(const Player& other) const {
        return name == other.name;
    }
};
