#include <utility>
#include "project1.h"

void bubble_sort(std::vector<int>& nums) {
	unsigned int size = nums.size();
	for (unsigned int i = 0; i < size; ++i) {
		for (unsigned int j = 1; j < size-i; ++j) {
			if (nums[j-1] > nums[j]) {
				std::swap(nums[j-1], nums[j]);
			}
		}
	}
}