#!/bin/bash

# 🔧 Compile
echo "🔧 Compiling..."
g++ -std=c++17 -o codebound main.cpp Character.cpp Player.cpp Enemy.cpp

# 🎮 Run simulated game (starts new game, fights once, saves, exits)
echo "🎮 Running game simulation..."
./codebound << EOF > test_output.txt
1               # New Game
TestPlayerBot   # Enter hero name
1               # Attack
1               # Attack
1               # Attack
1               # Attack
n               # No rematch
EOF

# 💾 Run again to test loading
echo "🔁 Loading saved game..."
./codebound << EOF >> test_output.txt
2               # Load Game
n               # Exit immediately
EOF

# 🧪 Check test output
echo "🧪 Checking test results..."
if grep -q "gained" test_output.txt; then
    echo "✅ XP Gained: PASS"
else
    echo "❌ XP Gained: FAIL"
fi

if grep -q "Game saved successfully" test_output.txt; then
    echo "✅ Save File Created: PASS"
else
    echo "❌ Save File Created: FAIL"
fi

if grep -q "Game loaded successfully" test_output.txt; then
    echo "✅ Save File Loaded: PASS"
else
    echo "❌ Save File Loaded: FAIL"
fi

echo "📄 Full output saved to test_output.txt"