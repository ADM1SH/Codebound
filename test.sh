#!/bin/bash

# 🔧 Compile
echo "🔧 Compiling..."
g++ -DTEST_MODE -std=c++17 -o codebound main.cpp Character.cpp Player.cpp Enemy.cpp

# ✅ Make sure previous output is cleared
rm -f test_output.txt

# 🎮 Simulated first run (new game, short fight, save)
echo "🎮 Running game simulation..."
./codebound > test_output.txt << EOF
1
TestPlayerBot
1
1
1
1
n
EOF

# 🔁 Test loading saved game (should skip battle)
echo "🔁 Loading saved game..."
./codebound >> test_output.txt << EOF
2
1
1
1
1
n
EOF

# ✅ Trim output to last 100 lines only if the file exists
if [ -f test_output.txt ]; then
    tail -n 100 test_output.txt > test_output_trimmed.txt
    mv test_output_trimmed.txt test_output.txt
else
    echo "⚠️ test_output.txt not found — skipping trim."
fi

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

echo "📄 Output saved to test_output.txt (size: $(du -h test_output.txt | cut -f1))"