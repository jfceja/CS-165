#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <utility>

void shuffle_vector(std::vector<int>& nums, const int& lenVector, std::mt19937& rng)
{
    for (int k = nums.size()-1; k >= 0; --k) {
		std::uniform_int_distribution<int> distribution(0, k);
		int j = distribution(rng);
		std::swap(nums[k], nums[j]);
	}
}

std::vector<int> getVector(const int& n) {
	std::vector<int> temp (n, 0);
	for (int i = 1; i <= n; ++i) {
		temp[i-1] = i;
	}
	return temp;
}

// might not want to use this, makes too many copies, which is a problem
// for very large vectors
std::vector<std::vector<int>> randomVectors(const int& numVectors, const int& lenVector, int seed = time(0)) {
	std::mt19937 rng = std::mt19937 (seed);
	std::vector<std::vector<int>> perms;
	for (int i = 0; i < numVectors; ++i) {
		perms.push_back(getVector(lenVector));
	}
	for (int i = 0; i < numVectors; ++i) {
		shuffle_vector(perms[i], lenVector, rng);
	}
	return perms;
}

int main()
{
    int numVectors = 30;
	int lenVector = 15;
	std::mt19937 rng = std::mt19937 (time(0));
	std::vector<std::vector<int>> perms;
	for (int i = 0; i < numVectors; ++i) {
		perms.push_back(getVector(lenVector));
	}
	for (int i = 0; i < numVectors; ++i) {
		shuffle_vector(perms[i], lenVector, rng);
	}
    for(int i = 0; i < numVectors; i++)
    {
        for(int num : perms[i])
            std::cout << num << " ";
        std::cout << "\n";
    }
    return 0;
}