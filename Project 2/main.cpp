#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <chrono>
#include "project2.h"

enum Algo {
	NF,
	FF,
	BF,
	FFD,
	BFD
};

double waste(const std::vector<double>& items, const std::vector<double>& free_space) {
	double sum = 0;
	for (const auto& n : items) {
		sum += n;
	}
	return free_space.size() - sum;
}

void fillItems(std::vector<double>& items, int n) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng = std::mt19937(seed);
	std::uniform_real_distribution<double> dist (0.0, 1.0);
	for (int i = 0; i < n; ++i) {
		items.push_back(dist(rng));
	}
}

void printBins(const std::vector<int>& assignment, const std::vector<double>& free_space) {
	for (int i = 0; i < assignment.size(); ++i) {
		std::cout << assignment[i] << "\t";
	}
	std::cout << "\n" << std::endl;
	for (int i = 0; i < free_space.size(); ++i) {
		std::cout << free_space[i] << "\t";
	}
	std::cout << "\n" << std::endl;
}

void create_empty_timings_file(std::string filename) {
	std::ofstream f;
	f.open(filename, std::ios::trunc);
	f << "funcname,sz,waste\n";
	f.close();
}
void add_timings_to_file(std::string funcname, int sz, double waste, std::string filename) {
	std::ofstream f;
	f.open(filename, std::ios::app);
	f << funcname << "," << sz << "," << waste << "\n";
	f.close();
}

int main() {
	int N = 200000;
	int nAlgos = 5;
	int reps = 64;
	std::vector<std::string> str {"Next-fit", "First-fit", "Best-fit", "First-fit decreasing", "Best-fit decreasing"};
	std::vector<std::string> files {"NF3.csv", "FF3.csv", "BF3.csv", "FFD3.csv", "BFD3.csv"};

	// execute the algorithms on the vectors
	for (int i = 0; i < nAlgos; ++i) {
		
		if (i != 4)
			continue; 
		
		std::cout << "Executing " << str[i] << std::endl;
		create_empty_timings_file(files[i]);
		for (int sz = 10; sz <= N; sz *= 2) {
			std::cout << "\tSize: " << sz << " ";
			double sum = 0;
			for (int r = 0; r < reps; ++r) {
				std::vector<double> items;
				fillItems(items, sz);
				std::vector<int> assignments (sz, 0);
				std::vector<double> free_spaces;
				std::cout << r << " ";
				std::cout << std::flush;
				switch(i) {
					case Algo::NF:
						next_fit(items, assignments, free_spaces);
					break;
					case Algo::FF:
						first_fit(items, assignments, free_spaces);
					break;

					case Algo::BF:
						best_fit(items, assignments, free_spaces);
					break;

					case Algo::FFD:
						first_fit_decreasing(items, assignments, free_spaces);
					break;

					case Algo::BFD:
						best_fit_decreasing(items, assignments, free_spaces);
					break;
				}
				//std::cout << "\t\tWaste: " << waste(items, free_spaces) << std::endl;
				sum += waste(items, free_spaces);
			}
			//printBins(assignments[i], free_spaces[i]);
			//std::cout << "Waste: " << waste(items, free_spaces[i]);
			//std::cout << std::endl;
			std::cout << "\n\tFor sz " << sz << " TOTAL waste is " << (sum/reps) << std::endl;
			add_timings_to_file(str[i], sz, sum/reps, files[i]);
		}
	}

	return 0;
}

