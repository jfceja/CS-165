#include <utility>
#include <random>
#include <algorithm> // std::min, std::max
#include <ctime>
#include "project1.h"

void annealing_sort(std::vector<int>& nums, const std::vector<int>& temps, const std::vector<int>& reps) {
	std::mt19937 g1(time(0)); // arbitrary seed
	
    for (unsigned int j = 0; j < temps.size(); ++j) {
		for (unsigned int i = 0; i < nums.size() - 1; ++i) {
			for (unsigned int k = 0; k < reps[j]; ++k) {
				// let s be a random int in range {i+1, min{n, i + Tj]}
				int r = std::min(nums.size()-1, i + temps[j]);
				std::uniform_int_distribution<int> distribution(i, std::min(nums.size()- 1, i + temps[j]));
				unsigned int s = distribution(g1);
				if (nums[i] > nums[s]) {
					std::swap(nums[i], nums[s]);
				}
			}
		}
		for (unsigned int i = nums.size()-1; i >= 1; --i) {
			for (unsigned int k = 0; k < reps[j]; ++k) {
				// let s be a random int in range {max(1, i-Tj), i-1}
				int r = std::max(0, ((int)i) - temps[j])-1;
				std::uniform_int_distribution<int> distribution(std::max(0, ((int)i) - temps[j]-1), i - 1);
				unsigned int s = distribution(g1);
				if (nums[s] > nums[i]) {
					std::swap(nums[i], nums[s]);
				}
			}
		}
	}

}