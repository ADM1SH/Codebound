// Player.cpp
#include <fstream>
#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(string name)
    : Character(name, 1, 100, 15, 5), xp(0), gold(0) {}

void Player::attack(Character& target) {
    int dmg = rand() % 10 + atk;
    cout << name << " attacks for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}

void Player::levelUp() {
    level++;
    maxHp += 20;
    atk += 5;
    def += 2;
    hp = maxHp;
    cout << name << " leveled up! Now level " << level << ".\n";
}

void Player::displayStats() const {
    Character::displayStats();
    cout << "XP: " << xp << " | Gold: " << gold << "\n";
}

void Player::addXP(int amount) {
    xp += amount;
    cout << name << " gained " << amount << " XP!\n";

    // XP needed to level up = level * 100
    if (xp >= level * 100) {
        xp -= level * 100;
        levelUp();
    }
}

void Player::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "❌ Failed to save game.\n";
        return;
    }

    file << name << "\n"
         << level << "\n"
         << hp << "\n"
         << maxHp << "\n"
         << xp << "\n"
         << atk << "\n"
         << def << "\n"
         << gold << "\n";

    // Save inventory
    file << inventory.size() << "\n";
    for (const auto& item : inventory) {
        file << item << "\n";
    }

    file.close();
    cout << "💾 Game saved successfully!\n";
}

bool Player::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "❌ No saved game found.\n";
        return false;
    }

    int invSize;
    file >> ws;
    getline(file, name);
    file >> level >> hp >> maxHp >> xp >> atk >> def >> gold;
    file >> invSize;
    file.ignore();

    inventory.clear();
    for (int i = 0; i < invSize; i++) {
        string item;
        getline(file, item);
        inventory.push_back(item);
    }

    file.close();
    cout << "✅ Game loaded successfully!\n";
    return true;
}