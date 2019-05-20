#include "project2.h"
#include <cstdint>
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <climits>

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
	std::vector<std::pair<double, int>> sortMap;
	std::vector<std::pair<double, int>> sortMap2;
	for (int i = 0; i < items.size(); ++i) {
		sortMap.push_back(std::make_pair(items[i], i));
	}
	std::sort(sortMap.begin(), sortMap.end(), [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
		return a.first > b.first;
	});
	std::sort(items_.rbegin(), items_.rend());
	first_fit(items_, assignment, free_space);
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
