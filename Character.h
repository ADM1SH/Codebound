// Character.h
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
protected:
    std::string name;
    int level;
    int hp, maxHp;
    int atk, def;

public:
    Character(std::string name, int level, int hp, int atk, int def);
    virtual void attack(Character& target) = 0;
    void takeDamage(int dmg);
    bool isAlive() const;
    virtual void displayStats() const;
    virtual ~Character() {}
};

#endif