#!/bin/bash

# Compile
echo "🔧 Compiling..."
g++ -std=c++17 -o codebound main.cpp Character.cpp Player.cpp Enemy.cpp

# Run and save output
echo "🎮 Running game simulation..."
./codebound << EOF > test_output.txt
TestPlayer
1
1
1
1
n
EOF

# Display summary
echo "🧪 Checking test results..."
if grep -q "gained" test_output.txt; then
    echo "✅ Test Passed: XP was gained."
else
    echo "❌ Test Failed: No XP gained."
fi

if grep -q "You defeated" test_output.txt; then
    echo "🏆 Victory achieved."
else
    echo "💀 Player was defeated or issue occurred."
fi

echo "📄 Full output saved to test_output.txt"