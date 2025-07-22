// Player.cpp
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