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
