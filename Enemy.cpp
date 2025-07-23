// Enemy.cpp
#include "Enemy.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Enemy::Enemy(string type, int level, int hp, int atk, int def)
    : Character(type, level, hp, atk, def), type(type), usedSpecial(false) {}

void Enemy::useSpecial(Character& target) {
    if (!usedSpecial) {
        int dmg = atk * 2;
        cout << type << " uses a special attack for " << dmg << " damage!\n";
        target.takeDamage(dmg);
        usedSpecial = true;
    } else {
        attack(target); // fallback to normal attack
    }
}

void Enemy::attack(Character& target) {
    if (!usedSpecial && (rand() % 3 == 0)) {
        useSpecial(target);
    } else {
        int dmg = rand() % 8 + atk;
        cout << type << " attacks you for " << dmg << " damage!\n";
        target.takeDamage(dmg);
    }
}

void Enemy::displayStats() const {
    cout << type << " (Enemy) - Level " << level << "\n";
    cout << "HP: " << hp << "/" << maxHp
         << " | ATK: " << atk << " | DEF: " << def
         << " | Special: " << (usedSpecial ? "Used" : "Ready") << "\n";
}

// Example enemy generator
Enemy Enemy::generateRandomEnemy(int difficulty) {
    string types[] = { "Goblin", "Slime", "Skeleton", "Wolf" };
    string type = types[rand() % 4];

    int level = difficulty;
    int hp = 30 + rand() % 20 + level * 5;
    int atk = 5 + rand() % 5 + level;
    int def = 2 + rand() % 3;

    return Enemy(type, level, hp, atk, def);
}