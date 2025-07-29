#include "Character.h"
#include <iostream>

using namespace std;

Character::Character(string name, int level, int hp, int atk, int def)
    : name(name), level(level), hp(hp), maxHp(hp), atk(atk), def(def) {}

void Character::takeDamage(int dmg) {
    int reduced = dmg - def;
    if (reduced < 1) reduced = 1;
    hp -= reduced;
    if (hp < 0) hp = 0;
}

bool Character::isAlive() const {
    return hp > 0;
}

void Character::displayStats() const {
    cout << name << " - Level " << level << "\n";
    cout << "HP: " << hp << "/" << maxHp << " | ATK: " << atk << " | DEF: " << def << "\n";
}

void Character::useSpecial(Character& target) {
    // Default implementation: do nothing
}