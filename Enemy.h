// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <string>

using namespace std;

class Enemy : public Character {
private:
    string type;

public:
    Enemy(string type, int level, int hp, int atk, int def);
    void attack(Character& target) override;
    void displayStats() const override;

    static Enemy generateRandomEnemy(int difficulty);
};

#endif