#include "Boss.h"
#include "Player.h"
#include <iostream>
using namespace std;

void Boss::useSpecial(Character& target) {
    Player& player = dynamic_cast<Player&>(target);

    std::cout << "👑 The Undead King lets out a chilling roar, draining your vitality!\n";
    int damage = this->atk + 30; // Extra powerful attack
    player.takeDamage(damage);
    std::cout << "💥 You take " << damage << " damage from the Undead King's wrath!\n";

    std::cout << getName() << " channels a dark curse!\n";

    // Inflict stun
    player.setStunned(true);
    std::cout << "⚡ " << player.getName() << " is stunned and will miss the next turn!\n";

    // Inflict ATK debuff for 2 turns
    player.modifyTempAtk(-15);
    player.setAtkDebuffTurns(2);
    std::cout << "🔻 " << player.getName() << "'s ATK dropped by 15 for 2 turns!\n";

    specialUsed = true;
}
