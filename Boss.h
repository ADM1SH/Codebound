#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
#include <iostream>

class Boss : public Enemy {
private:
    bool themePlayed;
    bool specialUsed;

public:
    int getCurrentHP() const;
    int getMaxHP() const;
    Boss()
        : Enemy("Undead King", 30, 1000, 150, 60), themePlayed(false), specialUsed(false) {}

    Boss(const std::string& name, int level, int hp, int atk, int def)
        : Enemy(name, level, hp, atk, def), themePlayed(false), specialUsed(false) {}

    void useSpecial(Character& target) override;
    bool hasPlayedTheme() const { return themePlayed; }
    void markThemePlayed() { themePlayed = true; }

    bool hasUsedSpecial() const { return specialUsed; }
    void markSpecialUsed() { specialUsed = true; }

    virtual ~Boss() = default;
};

#endif // BOSS_H