#include <iostream>
#include <random>
#include <fstream>
#include <string>
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
	std::mt19937 rng = std::mt19937(19937);
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
	int N = 1000;
	int nAlgos = 5;
	std::vector<std::string> str {"Next-fit", "First-fit", "Best-fit", "First-fit decreasing", "Best-fit decreasing"};
	std::vector<std::string> files {"NF.csv", "FF.csv", "BF.csv", "FFD.csv", "BFD.csv"};

	// execute the algorithms on the vectors
	for (int i = 0; i < nAlgos; ++i) {
		create_empty_timings_file(files[i]);
		for (int sz = 10; sz <= N; sz *= 2) {
			std::vector<double> items;
			fillItems(items, sz);
			std::vector<int> assignments (sz, 0);
			std::vector<double> free_spaces;

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
			//std::cout << str[i] << std::endl;
			//printBins(assignments[i], free_spaces[i]);
			//std::cout << "Waste: " << waste(items, free_spaces[i]);
			//std::cout << std::endl;
			add_timings_to_file(str[i], sz, waste(items, free_spaces), files[i]);
		}
	}

	return 0;
}

