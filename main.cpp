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
    cout << "\n--- Your Stats ---\n";
    player.displayStats();

    bool playing = true;

    while (playing) {
        Enemy enemy = Enemy::generateRandomEnemy(player.getLevel());

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
            int earnedXP = enemy.getLevel() * 50;
            player.addXP(earnedXP);
        } else {
            cout << "\nYou were defeated by the " << enemy.getName() << "...\n";
            playing = false;
            break;
        }

        cout << "\nWould you like to battle again? (Y/N): ";
        char again;
        cin >> again;
        if (again != 'Y' && again != 'y') {
            playing = false;
        }
    }

    cout << "\n=== GAME OVER ===\n";
    cout << "Thanks for playing Codebound!\n";
    return 0;
}