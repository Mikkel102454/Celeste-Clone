libs=-luser32
warnings="-Wno-writable-strings -Wno-format-security"

clear
clang++ -g src/main.cpp -o game.exe $libs $warnings
./game.exe