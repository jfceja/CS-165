#include <utility>
#include <random>
#include "project1.h"

bool isSorted(const std::vector<int>& nums) {
	unsigned int size = nums.size();
	for (unsigned int i = 1; i < size; ++i) {
		if (nums[i] < nums[i-1]) {
			return false;
		}
	}
	return true;
}

void spin_the_bottle_sort(std::vector<int>& nums) {
	unsigned int size = nums.size();
	std::mt19937 g1(19937); // arbitrary seed
	std::uniform_int_distribution<int> distribution(0, size-1);
	while(!isSorted(nums)) {
		for (unsigned int i = 0; i < size; ++i) {
			unsigned int s = distribution(g1);
			if ((i < s && nums[i] > nums[s]) || (i > s && nums[i] < nums[s])) {
				std::swap(nums[i], nums[s]);
			}
		}
	}
}