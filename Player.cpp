// Player.cpp
#include <fstream>
#include <algorithm>
#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(string name)
    : Character(name, 1, 100, 15, 5), xp(0), gold(0), mp(50) {
    inventory.push_back("Potion");
    inventory.push_back("Potion");
}

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
    cout << "XP: " << xp << " | Gold: " << gold << " | MP: " << mp << "\n";

    // Show HP bar
    int barWidth = 20;
    int filled = (hp * barWidth) / maxHp;
    cout << "HP: [";
    for (int i = 0; i < barWidth; ++i) {
        cout << (i < filled ? "#" : "-");
    }
    cout << "] " << hp << "/" << maxHp << "\n";
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

void Player::addItem(const string& item) {
    inventory.push_back(item);
    cout << item << " added to inventory.\n";
}

std::vector<std::string>& Player::getInventory() {
    return inventory;
}

void Player::useItem(const string& item) {
    auto it = find(inventory.begin(), inventory.end(), item);
    if (it == inventory.end()) {
        cout << "❌ No " << item << " in inventory.\n";
        return;
    }

    if (item == "Potion") {
        int heal = 30;
        hp = min(hp + heal, maxHp);
        cout << name << " used a Potion and restored " << heal << " HP!\n";
    } else if (item == "Elixir") {
        hp = maxHp;
        cout << name << " used an Elixir and fully restored HP!\n";
    } else if (item == "Bomb") {
        cout << name << " threw a Bomb! (💥 Enemy takes 50 damage — apply manually in main)\n";
    } else if (item == "Shield") {
        def += 5;
        cout << name << " used a Shield! Defense increased by 5 this battle.\n";
    } else if (item == "Mana Potion") {
        int restore = 30;
        mp += restore;
        cout << name << " drank a Mana Potion! MP restored by " << restore << ".\n";
    } else {
        cout << "⚠️ Unknown item.\n";
        return;
    }

    inventory.erase(it);  // remove used item
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
         << gold << "\n"
         << mp << "\n";

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
    file >> level >> hp >> maxHp >> xp >> atk >> def >> gold >> mp;
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

void Player::displayInventoryWithIndex() const {
    cout << "Inventory:\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ". " << inventory[i] << "\n";
    }
}

void Player::useItemByIndex(int index) {
    if (index < 1 || index > static_cast<int>(inventory.size())) {
        cout << "❌ Invalid item selection.\n";
        return;
    }
    useItem(inventory[index - 1]);
}