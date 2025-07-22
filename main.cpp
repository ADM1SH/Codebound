// main.cpp
#include "Player.h"
#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Seed RNG

    cout << "Welcome to Codebound!\n";
    cout << "Enter your hero's name: ";
    string playerName;
    getline(cin, playerName);

    Player player(playerName);
    Enemy enemy = Enemy::generateRandomEnemy(player.getLevel());

    cout << "\n--- Your Stats ---\n";
    player.displayStats();
    cout << "\n--- Enemy Appears! ---\n";
    enemy.displayStats();

    cout << "\n=== BATTLE START ===\n";

    while (player.isAlive() && enemy.isAlive()) {
        cout << "\nYour Turn:\n";
        cout << "1. Attack\n2. View Stats\nChoose: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            player.attack(enemy);
        } else {
            player.displayStats();
            continue;
        }

        if (enemy.isAlive()) {
            cout << "\nEnemy's Turn:\n";
            enemy.attack(player);
        }
    }

    if (player.isAlive()) {
        cout << "\nYou defeated the " << enemy.getName() << "!\n";
    } else {
        cout << "\nYou were defeated by the " << enemy.getName() << "...\n";
    }

    cout << "\n=== GAME OVER ===\n";
    return 0;
}