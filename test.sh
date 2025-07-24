#!/bin/bash

# 🔧 Compile
echo "🔧 Compiling..."
/opt/homebrew/opt/llvm/bin/clang++ \
  -std=gnu++17 -stdlib=libc++ \
  -Iinclude \
  main.cpp Character.cpp Player.cpp Enemy.cpp Leaderboard.cpp \
  -o codebound \
  -L/opt/homebrew/opt/llvm/lib

# ✅ Clean old output
rm -f test_output.txt

# 🎮 Run simulation 1
echo "🎮 Running game simulation..."
./codebound > test_output.txt << EOF
1
TestPlayerBot
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
1
n
EOF

# 🔁 Load and test save
echo "🔁 Loading saved game..."
./codebound >> test_output.txt << EOF
2
1
1
1
1
1
1
1
1
1
n
EOF

# 💾 Test alternate slot
echo "💾 Testing alternate save slot..."
./codebound >> test_output.txt << EOF
1
SlotTwoPlayer
1
1
1
1
1
1
1
1
1
1
1
1
1
n
EOF

# ✅ Trim output
if [[ -f test_output.txt ]]; then
  tail -n 100 test_output.txt > test_output_trimmed.txt
  mv test_output_trimmed.txt test_output.txt
else
  echo "⚠️ No test_output.txt — skipping trim."
fi

# 🧪 Assertions
echo "🧪 Checking test results..."
grep -q "gained" test_output.txt && echo "✅ XP Gained: PASS" || echo "❌ XP Gained: FAIL"
grep -q "Game saved successfully" test_output.txt && echo "✅ Save File Created: PASS" || echo "❌ Save File Created: FAIL"
grep -q "Game loaded successfully" test_output.txt && echo "✅ Save File Loaded: PASS" || echo "❌ Save File Loaded: FAIL"
grep -q "used a Potion" test_output.txt && echo "✅ Item Used in Battle: PASS" || echo "❌ Item Used in Battle: FAIL"
grep -q "SlotTwoPlayer" test_output.txt && echo "✅ Alternate Save Slot: PASS" || echo "❌ Alternate Save Slot: FAIL"

echo "📄 Output saved (size: $(du -h test_output.txt | cut -f1))"