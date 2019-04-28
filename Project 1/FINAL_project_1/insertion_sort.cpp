#include <utility>
#include "project1.h"

void insertion_sort(std::vector<int>& nums) {
	unsigned int size = nums.size();
	for (unsigned int i = 1; i < size; ++i) {
		int temp = nums[i];
		
		// slide elements down to make room for a[i]
		int j = i;
		while (j > 0 && nums[j-1] > temp) {
			nums[j] = nums[j-1];
			--j;
		}
		nums[j] = temp;
	}	
}