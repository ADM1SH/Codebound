#include "Leaderboard.h"
#include "Player.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

LeaderboardEntry::LeaderboardEntry(std::string name, int level, int xp)
    : name(std::move(name)), level(level), xp(xp) {}
using namespace std;

static std::vector<LeaderboardEntry> entries;

void Leaderboard::loadFromFile(const std::string& filename) {
    entries.clear();
    std::ifstream file(filename);
    if (!file.is_open()) return;

    json j;
    file >> j;
    entries = j.get<std::vector<LeaderboardEntry>>();
}

void Leaderboard::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return;

    json j = entries;
    file << j.dump(4); // Pretty print with 4-space indentation
}

// Update an existing entry or add a new one if not found
void Leaderboard::addOrUpdateEntry(const std::string& name, int level, int xp) {
    for (auto& entry : entries) {
        if (entry.name == name) {
            if (level > entry.level || (level == entry.level && xp > entry.xp)) {
                entry.level = level;
                entry.xp = xp;
            }
            return;
        }
    }
    entries.push_back({ name, level, xp });
}

void Leaderboard::sortLeaderboard() {
    std::sort(entries.begin(), entries.end(), [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
        if (a.level != b.level) return a.level > b.level;
        return a.xp > b.xp;
    });
}

void Leaderboard::display() {
    cout << "\n🏆 Leaderboard:\n";
    int rank = 1;
    for (const auto& entry : entries) {
        cout << rank++ << ". " << entry.name << " - Level " << entry.level << ", XP: " << entry.xp << "\n";
    }
}

void Leaderboard::clear() {
    entries.clear();
}

void to_json(json& j, const LeaderboardEntry& entry) {
    j = json{{"name", entry.name}, {"level", entry.level}, {"xp", entry.xp}};
}

void from_json(const json& j, LeaderboardEntry& entry) {
    j.at("name").get_to(entry.name);
    j.at("level").get_to(entry.level);
    j.at("xp").get_to(entry.xp);
}