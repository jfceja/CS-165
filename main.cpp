#include <iostream>
#include <ctime>
#include <algorithm>
#include "project1.h"

int main() {
	std::vector<int> bubble;
	for (int i = 5000; i >= 0; --i)
		bubble.push_back(i);
	std::vector<int> insertion = bubble;
	std::vector<int> spinBottle = bubble;
    std::vector<int> shell = bubble;
	std::vector<int> annealing = bubble;
	std::vector<int> temperatures = bubble; // T = (t1, t2, ..., Tt) where Ti >= Ti+1 and Tt = 0
	std::vector<int> reps = bubble;
    
    
	std::clock_t c_start = clock();
	bubble_sort(bubble);
	std::clock_t c_end = clock();
	std::cout << "Bubble sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	
	c_start = clock();
	insertion_sort(insertion);
	c_end = clock();
	std::cout << "Insertion sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	
	c_start = clock();
	spin_the_bottle_sort(spinBottle);
	c_end = clock();
	std::cout << "Spin the bottle sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
    
    std::vector<int> gapSequence = shell;
    c_start = clock();
    shell_sort(shell, gapSequence);
    c_end = clock();
    std::cout << "shell sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	c_start = clock();
	annealing_sort(annealing, temperatures, reps);
	c_end = clock();
	
	return 0;
}