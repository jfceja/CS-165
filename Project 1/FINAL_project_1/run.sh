#!/bin/bash
g++ -std=c++11 -Wall annealing_sort.cpp bubble_sort.cpp shell_sort.cpp spin_the_bottle_sort.cpp insertion_sort.cpp main.cpp rng.cpp -o RUN_ME
chmod +x "RUN_ME"
echo "Executing the program..."
echo "Change line 126 in main.cpp to sort with partially sorted array."
./RUN_ME
