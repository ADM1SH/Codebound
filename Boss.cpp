#include "Boss.h"
#include <iostream>
using namespace std;

Boss::Boss(const std::string& name, int level, int hp, int atk, int def)
    : Enemy(name, level, hp, atk, def), phaseTwoTriggered(false) {}

int Boss::getCurrentHP() const {
    return hp;
}

int Boss::getMaxHP() const {
    return maxHp;
}

void Boss::checkPhaseTwo() {
    if (!phaseTwoTriggered && hp <= (maxHp / 4)) {
        cout << "🌀 The Undead King rises again... Stronger than before!" << endl;
        atk += 25;
        def += 20;
        phaseTwoTriggered = true;
    }
}

void Boss::useSpecial(Character& target) {
    cout << "👑 The Undead King unleashes a devastating curse!\n";
    target.takeDamage(atk + 40);
}
