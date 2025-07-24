// main.cpp
#include "Player.h"
#include "Enemy.h"
#include "Leaderboard.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

bool useItemByIndex(Player& player, int index);

int main(int argc, char* argv[]) {
    srand(time(0)); // Seed RNG

    Player player("Unnamed");

    bool testMode = (argc > 1 && std::string(argv[1]) == "test");

    if (testMode) {
        if (!player.loadFromFile("save_TestPlayerBot.txt")) {
            cout << "❌ Failed to load test save file.\n";
            return 1;
        }

        Enemy enemy = Enemy::generateRandomEnemy(player.getLevel());

        cout << "\n--- Enemy Appears! ---\n";
        enemy.displayStats();
        cout << "\n=== BATTLE START ===\n";
        player.useItem("Potion");

        for (int turn = 1; turn <= 2 && player.isAlive() && enemy.isAlive(); ++turn) {
            cout << "\nYour Turn:\n";
            player.attack(enemy);

            if (enemy.isAlive()) {
                cout << "\nEnemy's Turn:\n";
                enemy.attack(player);
            }
        }

        if (player.isAlive()) {
            cout << "\nYou defeated the " << enemy.getName() << "!\n";
            int earnedXP = enemy.getLevel() * 50;
            player.addXP(earnedXP);
            player.saveToFile("save_" + player.getName() + ".txt");
            Leaderboard lb;
            lb.loadFromFile("leaderboard.json");
            lb.addOrUpdateEntry(player.getName(), player.getLevel(), player.getXP());
            lb.sortLeaderboard();
            lb.saveToFile("leaderboard.json");
        } else {
            cout << "\nYou were defeated by the " << enemy.getName() << "...\n";
        }

        cout << "\n=== GAME OVER ===\n";
        cout << "Thanks for playing Codebound!\n";
        return 0;
    }

    cout << "Welcome to Codebound!\n";
    cout << "1. New Game\n2. Load Game\n3. View Leaderboard\nChoose: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 3) {
        Leaderboard lb;
        lb.loadFromFile("leaderboard.json");
        lb.sortLeaderboard();
        lb.display();
        return 0;
    }

    if (choice == 2) {
        cout << "Available Save Slots:\n";
        vector<string> saves;
        for (const auto& entry : fs::directory_iterator(".")) {
            std::string fname = entry.path().filename().string();
            if (fname.rfind("save_", 0) == 0 && fname.size() > 4 && fname.substr(fname.size() - 4) == ".txt") {
                saves.push_back(fname);
            }
        }

        if (saves.empty()) {
            cout << "No save files found.\n";
            return 0;
        }

        for (size_t i = 0; i < saves.size(); ++i) {
            cout << i + 1 << ". " << saves[i] << "\n";
        }

        cout << "Choose a save slot: ";
        int slot;
        cin >> slot;
        cin.ignore();

        if (slot < 1 || static_cast<size_t>(slot) > saves.size()) {
            cout << "Invalid selection.\n";
            return 0;
        }

        if (!player.loadFromFile(saves[slot - 1])) {
            cout << "❌ Failed to load save file.\n";
            return 0;
        } else {
            cout << "✅ Game loaded successfully!" << endl;
        }

        cout << "\n--- Your Stats ---\n";
        player.displayStats();
    } else {
        cout << "Enter your hero's name: ";
        string name;
        getline(cin, name);
        player = Player(name);
        player.getInventory().push_back("Potion");
        player.getInventory().push_back("Elixir");
    }


    bool playing = true;
    while (playing) {
        const int waveSize = 3;
        std::vector<Enemy> enemyWave;
        for (int i = 0; i < waveSize; ++i) {
            enemyWave.push_back(Enemy::generateRandomEnemy(player.getLevel()));
        }

        for (size_t i = 0; i < enemyWave.size(); ++i) {
            Enemy& enemy = enemyWave[i];

            cout << "\n🌊 Wave " << (i + 1) << " of " << waveSize << endl;
            cout << "\n--- Enemy Appears! ---\n";
            enemy.displayStats();
            cout << "\n=== BATTLE START ===\n";

            while (player.isAlive() && enemy.isAlive()) {
                cout << "\nYour Turn:\n";
                cout << "1. Attack\n2. View Stats\n3. Use Item\nChoose: ";
                int choice;
                cin >> choice;
                cin.ignore();

                if (choice == 1) {
                    player.attack(enemy);
                }
                else if (choice == 2) {
                    player.displayStats();  
                    continue;
                }
                else if (choice == 3) {
                    player.displayInventoryWithIndex();
                    cout << "Choose item number (or 0 to cancel): ";
                    int index;
                    cin >> index;
                    cin.ignore();

                    if (index == 0) {
                        cout << "Cancelled item use.\n";
                        continue;
                    }
                    bool success = false;
                    player.useItemByIndex(index - 1, success);
                    if (!success) {
                        cout << "❌ Invalid item selection.\n";
                        continue;
                    }
                    cout << "✅ Item used in battle.\n";
                }
                else {
                    cout << "🚫 Invalid choice. Please enter 1, 2, or 3.\n";
                    continue;
                }

                if (enemy.isAlive()) {
                    cout << "\nEnemy's Turn:\n";
                    enemy.decideAndAct(player);
                }
            }

            if (!player.isAlive()) {
                cout << "\nYou were defeated by the " << enemy.getName() << "...\n";
                playing = false;
                break;
            } else {
                cout << "\nYou defeated the " << enemy.getName() << "!\n";
                int earnedXP = enemy.getLevel() * 50;
                player.addXP(earnedXP);
            }
        }

        if (player.isAlive()) {
            cout << "🏆 You cleared all enemy waves!\n";
            player.addGold(100);  // bonus gold
            player.addXP(100);    // bonus XP
            player.saveToFile("save_" + player.getName() + ".txt");
            Leaderboard lb;
            lb.loadFromFile("leaderboard.json");
            lb.addOrUpdateEntry(player.getName(), player.getLevel(), player.getXP());
            lb.sortLeaderboard();
            lb.saveToFile("leaderboard.json");
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