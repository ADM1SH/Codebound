#include "Enemy.h"
#include "Character.h"
#include <iostream>

using namespace std;

Enemy::Enemy(string type, int level, int hp, int atk, int def)
    : Character(type, level, hp, atk, def) {}

void Enemy::decideAndAct(Character& target) {
    // Decide action: Special, Heal, or Attack

    bool acted = false;

    cout << "[DEBUG] Enemy HP: " << hp << "/" << maxHp << ", Special Used: " << usedSpecial << endl;

    // TODO: Add special attack variants (e.g., stun, slow) based on enemy type

    // Use special attack with 33% chance if not yet used
    if (!usedSpecial && rand() % 3 == 0) {
        cout << type << " is attempting a special attack!\n";
        useSpecial(target);
        acted = true;
    }

    // Only heal if HP < 40% and special already used, with a 50% chance
    // Try healing if HP is below 40% and special is used
    if (!acted && usedSpecial && hp < (maxHp * 0.4) && rand() % 100 < 50) {
        int heal = 15 + rand() % 16; // Heal 15–30 HP
        int oldHp = hp;
        hp += heal;
        if (hp > maxHp) hp = maxHp;
        usedSpecial = true;
        cout << type << " healed for " << (hp - oldHp) << " HP!\n";
        acted = true;
    }

    // Default attack
    if (!acted) {
        int dodgeChance = rand() % 100;
        if (dodgeChance < 20) {
            cout << type << " dodged the attack!\n";
            return;
        }
        int dmg = rand() % 8 + atk;
        cout << type << " attacks you for " << dmg << " damage!\n";
        target.takeDamage(dmg);
    }
}
void Enemy::useSpecial(Character& target) {
    if (type == "Goblin") {
        // Goblin special: Strong hit + stun (sets a "stunned" flag externally if implemented)
        int specialDmg = atk + 20 + rand() % 10;
        cout << type << " uses a furious strike for " << specialDmg << " damage and stuns you!\n";
        target.takeDamage(specialDmg);
        // Optional: set a stunned flag on target here
    }
    else if (type == "Slime") {
        // Slime special: Slows target (reduce ATK temporarily if supported)
        int specialDmg = atk + 10 + rand() % 5;
        cout << type << " spits slime for " << specialDmg << " damage! Your attack power is reduced!\n";
        target.takeDamage(specialDmg);
        // Optional: reduce target.atk here temporarily
    }
    else if (type == "Skeleton") {
        // Skeleton special: Armor pierce (ignore DEF)
        int specialDmg = atk + 15 + rand() % 8;
        cout << type << " performs a bone-shattering attack ignoring your defense!\n";
        // Apply damage directly, ignoring defense (if defense is considered elsewhere)
        target.takeDamage(specialDmg); // You could bypass DEF manually if needed
    }
    else if (type == "Wolf") {
        // Wolf special: Two quick hits
        int hit1 = atk + rand() % 5;
        int hit2 = atk + rand() % 5;
        cout << type << " unleashes a flurry of attacks for " << hit1 << " and " << hit2 << " damage!\n";
        target.takeDamage(hit1);
        target.takeDamage(hit2);
    }
    else {
        // Fallback default special
        int specialDmg = atk + 15 + rand() % 10;
        cout << type << " uses a special attack for " << specialDmg << " damage!\n";
        target.takeDamage(specialDmg);
    }

    usedSpecial = true;
}

Enemy Enemy::generateRandomEnemy(int level) {
    string types[] = {"Goblin", "Skeleton", "Wolf", "Slime"};
    string chosenType = types[rand() % 4];

    int baseHp = 30 + level * 5 + rand() % 10;
    int baseAtk = 5 + level * 2 + rand() % 4;
    int baseDef = 2 + level + rand() % 3;

    Enemy newEnemy(chosenType, level, baseHp, baseAtk, baseDef);
    newEnemy.type = chosenType;
    return newEnemy;
}

void Enemy::attack(Character& target) {
    int dmg = atk + (rand() % 6);
    cout << type << " attacks you for " << dmg << " damage!\n";
    target.takeDamage(dmg);
}

void Enemy::displayStats() const {
    cout << type << " (Enemy) - Level " << level << endl;
    cout << "HP: " << hp << "/" << maxHp << " | ATK: " << atk << " | DEF: " << def;
    cout << " | Special: " << (usedSpecial ? "Used" : "Ready") << "\n";
}