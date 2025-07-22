// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <vector>
#include <string>

using namespace std;

class Player : public Character {
private:
    int xp;
    int gold;
    vector<string> inventory;

public:
    Player(string name);
    void attack(Character& target) override;
    void levelUp();
    void displayStats() const override;
};

#endif