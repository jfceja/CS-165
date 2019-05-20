#include "project2.h"
#include <cstdint>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <climits>
#include <utility>

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
	std::vector<std::pair<double, int>> sortMap;
	std::vector<std::pair<double, int>> sortMap2;
	for (int i = 0; i < items.size(); ++i) {
		sortMap.push_back(std::make_pair(items[i], i));
	}
	std::sort(sortMap.begin(), sortMap.end(), [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
		return a.first > b.first;
	});
	std::sort(items_.rbegin(), items_.rend());
	best_fit(items_, assignment, free_space);
	for (int i = 0; i < items.size(); ++i) {
		sortMap2.push_back(std::make_pair(sortMap[i].second, assignment[i]));
	}
	std::sort(sortMap2.begin(), sortMap2.end(), [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
		return a.first < b.first;
	});
	for (int i = 0; i < items.size(); ++i) {
		assignment[i] = sortMap2[i].second;
	}
}