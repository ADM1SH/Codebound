// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <vector>
#include <string>

using namespace std;

class Player : public Character {
private:
    bool stunned;
    int tempAtk;
    int xp;
    int gold;
    int mp;  // Mana points for magic-related items
    vector<string> inventory;
    int atkDebuffTurns = 0;

public:
// Player.h
    bool isStunned() const;
    void resetTempAtk();
    void setStunned(bool value);
    void modifyTempAtk(int amount);
    void addGold(int amount);
    std::vector<std::string>& getInventory();              // for push_back
    const std::vector<std::string>& getInventory() const;  // for display/read-only    
    void saveToFile(const string& filename);
    bool loadFromFile(const string& filename);
    void addXP(int amount);
    int getXP() const { return xp; }
    int getLevel() const { return level; }
    int getMP() const { return mp; }
    void setMP(int amount) { mp = amount; }
    int getAtkDebuffTurns() const;
    void decreaseAtkDebuffTurns();
    void setAtkDebuffTurns(int turns);
    Player(string name); // now initializes mp too
    void attack(Character& target) override;
    void levelUp();
    void displayStats() const override; // Displays full stats including inventory
    void useItem(const std::string& item);
    void addItem(const string& item);

    // Shows inventory with numbered list
    void displayInventoryWithIndex() const;

    // Uses item by choosing its index in inventory
    void useItemByIndex(int index, bool& success);
};

#endif