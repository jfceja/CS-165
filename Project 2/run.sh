#!/bin/bash
g++ -std=c++11 main.cpp best_fit.cpp first_fit.cpp next_fit.cpp -o RUN_ME.out
# just to be safe
chmod +x RUN_ME.o
echo "Executing the program..."
./RUN_ME.out
