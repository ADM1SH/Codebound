// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include <string>

using namespace std;

// Enemy class now includes smarter AI: special attacks, healing, and dodging.
class Enemy : public Character {
private:
    string type;
    bool usedSpecial;

    bool shouldUseSpecial() const;
    bool shouldHeal() const;
    bool shouldDodge() const;
    bool tryDodge() const;
    void healSelf();

public:
    Enemy(string type, int level, int hp, int atk, int def);
    void attack(Character& target) override;
    void displayStats() const override;
    void useSpecial(Character& target);
    void decideAndAct(Character& target);

    static Enemy generateRandomEnemy(int difficulty);
};

#endif