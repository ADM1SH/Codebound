#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "Player.h"
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

class LeaderboardEntry {
public:
    std::string name;
    int level;
    int xp;

    LeaderboardEntry() = default;
    LeaderboardEntry(std::string name, int level, int xp);
};

class Leaderboard {
public:
    static void savePlayerStats(const Player& player, const std::string& filename = "leaderboard.txt");
    static std::vector<LeaderboardEntry> loadLeaderboard(const std::string& filename = "leaderboard.txt");
    static void displayLeaderboard(const std::vector<LeaderboardEntry>& entries);
    static void saveToJSON(const std::vector<LeaderboardEntry>& entries, const std::string& filename = "leaderboard.json");
    static std::vector<LeaderboardEntry> loadFromJSON(const std::string& filename = "leaderboard.json");

    static void loadFromFile(const std::string& filename = "leaderboard.txt");
    static void saveToFile(const std::string& filename = "leaderboard.txt");
    static void addOrUpdateEntry(const std::string& name, int level, int xp);
    static void sortLeaderboard();
    static void display();
    static void clear();
};

void to_json(nlohmann::json& j, const LeaderboardEntry& entry);
void from_json(const nlohmann::json& j, LeaderboardEntry& entry);

#endif