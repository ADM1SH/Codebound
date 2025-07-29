# 🧠 Codebound: A Terminal RPG Adventure

```
 ____ ___  ____  _____ ____  ____  _   _ _   _ _   _ ____  
/ ___/ _ \|  _ \| ____|  _ \| __ )| | | | | | | \ | |  _ \ 
| |  | | | | | | |  _| | | | |  _ \| | | | | | |  \| | | |
| |__| |_| | |_| | |___| |_| | |_) | |_| | |_| | |\  | |_| 
\____\___/|____/|_____|____/|____/ \___/ \___/|_| \_|____/ 
```

## 🎮 Game Overview

**Codebound** is a C++ terminal-based RPG where players battle waves of enemies and defeat an ultimate boss. Designed with progressive leveling, items, enemy specials, and a leaderboard, it aims to deliver a satisfying tactical combat experience in the terminal.

---

## ⚔️ Features

- 📜 Turn-based battle system
- 💥 Enemy special attacks (stuns, debuffs, dodge, etc.)
- 👑 Boss fights with phase mechanics and special skills
- 🧪 Inventory and item usage
- 💾 Save/load system
- 🏆 Local leaderboard tracking
- 🎨 Visual HP bars for player and boss
- 🌀 Phase 2 system for unique boss behavior (in development)

---

## 🔧 How to Compile

```bash
clang++ -std=c++17 -Iinclude main.cpp Character.cpp Player.cpp Enemy.cpp Boss.cpp Leaderboard.cpp -o main
```

Then run:
```bash
./main
```

---

## 📁 File Structure

```
.
├── main.cpp            # Entry point of the game
├── Character.cpp/h     # Base class for Player and Enemies
├── Player.cpp/h        # Player logic and actions
├── Enemy.cpp/h         # Enemy behavior and special attacks
├── Boss.cpp/h          # Boss-specific behaviors and Phase 2 triggers
├── Leaderboard.cpp/h   # Leaderboard system (save/load)
├── README.md           # This file
└── save files/         # Player save slots
```

---

## 🛡️ Current Boss: Undead King

The **Undead King** has:
- A devastating special curse attack
- A visual HP bar
- Planned Phase 2 behavior when HP drops below 50%

---

## 🚧 Roadmap

- [x] Boss health bar
- [x] Boss special attacks
- [ ] Boss Phase 2 transformation
- [ ] Inventory UI menu
- [ ] Enemy variants
- [ ] Graphical UI (optional)

---

## 🧠 Credits

Developed by **Adam Anwar** — 2025  
Built for fun, practice, and mastery of C++ fundamentals through terminal games.

---

## 🧙‍♂️ ASCII Art Preview

```
       (    )
      ((((()))
      |o\ /o)|  💀 Undead King Awaits...
      ( (  _')
       (._.  /\__
      ,\___,/ '  ')
    '._   _/ /'---
      |__|   \    
     /_)__)_/_)
```

---

Happy hacking and stay Codebound!
