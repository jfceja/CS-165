#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <climits>
#include "project1.h"
/*
phase 1
	temperatures decreases in value 
	reps are all constants
phase 2
	temperatures decrease even quicker
	reps are a very low number (logn/loglogn)
phase 3
	temperatures don't decrease (all 1's)
	reps don't change (all 1's)
	short length??
*/

int main() {
	std::vector<int> bubble;
	int sz = 8000*16;
	int tz = 650;
	std::cout << "sz: " << sz << "tz: " << tz << std::endl;
	for (int i = sz-1; i >= 0; --i)
		bubble.push_back(i);
	std::vector<int> insertion = bubble;
	std::vector<int> spinBottle = bubble;
    std::vector<int> shell = bubble;
	std::vector<int> annealing = bubble;
	
	std::vector<int> temperatures (tz,  0); // T = (t1, t2, ..., Tt) where Ti >= Ti+1 and Tt = 0
	std::vector<int> reps (tz, 0);
	
	std::mt19937 g1(time(0)); // arbitrary seed
	std::uniform_int_distribution<int> distribution(31, 32);
	for (int i = 0; i < tz; ++i) {
		temperatures[i] = distribution(g1);
		//std::cout << temperatures[i] << std::endl;
		reps[i] = distribution(g1);
	}
	std::sort(temperatures.begin(), temperatures.end());
	std::reverse(temperatures.begin(), temperatures.end());
	temperatures[tz-1] = 0;
	std::cout << temperatures[0] << " " << temperatures[1] << " " << temperatures[tz-1] << std::endl;
	
	
	std::clock_t c_start = clock();
	//bubble_sort(bubble);
	std::clock_t c_end = clock();
	std::cout << "Bubble sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	
	c_start = clock();
	//insertion_sort(insertion);
	c_end = clock();
	std::cout << "Insertion sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	
	c_start = clock();
	//spin_the_bottle_sort(spinBottle);
	c_end = clock();
	std::cout << "Spin the bottle sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	std::cout << "isSorted = " << std::is_sorted(spinBottle.begin(), spinBottle.end()) << std::endl;
    
    std::vector<int> gapSequence = shell;
    c_start = clock();
    //shell_sort(shell, gapSequence);
    c_end = clock();
    std::cout << "shell sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	std::cout << "isSorted = " << std::is_sorted(shell.begin(), shell.end()) << std::endl;
	
	std::cout << "Before annealing sort\n";
	c_start = clock();
	annealing_sort(annealing, temperatures, reps);
	c_end = clock();
	std::cout << "annealing sort " << (float)(c_end-c_start)/CLOCKS_PER_SEC << std::endl;
	std::cout << "isSorted = " << std::is_sorted(annealing.begin(), annealing.end()) << std::endl;
	return 0;
}