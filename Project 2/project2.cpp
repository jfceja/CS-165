#include "project2.h"
#include <cstdint>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <climits>

void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	free_space.push_back(1);
	int j = 0;
	for (int i = 0; i < items.size(); ++i) {
		if (fabs(free_space[j] - items[i]) < DBL_EPSILON || free_space[j] > items[i]) {
			assignment[i] = j;
			free_space[j] -= items[i];
		}
		else {
			free_space.push_back(1);
			assignment[i] = ++j;
			free_space[j] -= items[i];
		}
	}
}

void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	for (int i = 0; i < items.size(); ++i) {
		bool found = false;
		for (int j = 0; j < free_space.size(); ++j) {
			if (fabs(free_space[j] - items[i]) < DBL_EPSILON || free_space[j] > items[i]) {
				found = true;
				assignment[i] = j;
				free_space[j] -= items[i];
				break;
			}
		}
		if (!found) {
			free_space.push_back(1);
			assignment[i] = free_space.size()-1;
			free_space.back() -= items[i];
		}
	}
}

void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	std::vector<double> items_ = items;
	std::sort(items_.rbegin(), items_.rend());
	first_fit(items_, assignment, free_space);
}

void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	for (int i = 0; i < items.size(); ++i) {
		double best = DBL_MAX;
		int bestIndex = -1;
		for (int j = 0; j < free_space.size(); ++j) {
			double gapSize = free_space[j]-items[i];

			// if the gap size is >= 0
			if (fabs(gapSize) < DBL_EPSILON || gapSize > 0) {
				if (gapSize < best) {
					best = gapSize;
					bestIndex = j;
				}
			}
		}
		if (best < DBL_MAX) {
			assignment[i] = bestIndex;
			free_space[bestIndex] -= items[i];
		}
		else {
			free_space.push_back(1);
			free_space.back() -= items[i];
			assignment[i] = free_space.size() - 1;
		}
	}
}

void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	std::vector<double> items_ = items;
	std::sort(items_.rbegin(), items_.rend());
	best_fit(items_, assignment, free_space);
}