#include <utility>
#include "project1.h"

void shell_sort(std::vector<int>& nums, const std::vector<int>& gaps) {
    unsigned int numsSize = nums.size();
    unsigned int gapSize = gaps.size();
	for (unsigned int _gap = 0; _gap < gapSize; ++_gap) {
        unsigned int gap = gaps[_gap];
        for (unsigned int i = gap; i < numsSize; ++i) {
            // slide element i back by gap indexes
            // until it's "in order"
            int temp = nums[i];
            unsigned int j = i;
            while (j >= gap && temp < nums[j - gap]) {
                nums[j] = nums[j - gap];
                j -= gap;
            }
            nums[j] = temp;
        }
    }
}