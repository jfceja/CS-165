#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>
#include "rng.h"

void shuffle_vector(std::vector<int>& nums, std::mt19937& rng)
{
    for (int k = nums.size()-1; k >= 0; --k) {
		std::uniform_int_distribution<int> distribution(0, k);
		int j = distribution(rng);
		std::swap(nums[k], nums[j]);
	}
}

// input array should be sorted
void partial_shuffle_vector(std::vector<int>& nums, std::mt19937& rng) {
	std::uniform_int_distribution<int> distribution(0, nums.size()-1);
	int lim = 2 * log2(nums.size());
	for (int i = 0; i < lim; ++i) {
		int l = distribution(rng);
		int r = distribution(rng);
		std::swap(nums[l], nums[r]);
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
std::vector<std::vector<int>> randomVectors(const int& numVectors, const int& lenVector, int seed) {
	std::mt19937 rng = std::mt19937 (seed);
	std::vector<std::vector<int>> perms;
	for (int i = 0; i < numVectors; ++i) {
		perms.push_back(getVector(lenVector));
	}
	for (int i = 0; i < numVectors; ++i) {
		shuffle_vector(perms[i], rng);
	}
	return perms;
}

std::vector<int> bestGapSequence() {
	// Ciura series
	// https://en.wikipedia.org/wiki/Shellsort#Gap_sequences
	return std::vector<int> {1, 4, 10, 23, 57, 132, 301, 701};
}

// do not pass in n <= 0
std::vector<int> fib_of_n(int n) {
	std::vector<int> res = {1, 1};
	if (n == 1) {
		return std::vector<int> {1};
	}
	else if (n == 2) {
		return res;
	}

	for (int i = 2; i < n; ++i) {
		res.push_back(res[res.size()-1] + res[res.size()-2]);
	}
	return res;
}
// grows quicker
std::vector<int> johnnyFibSequence(int n, int multi) {
	int sz = multi*(floor(log2(n))+1);
	std::vector<int> fib = fib_of_n(sz);
	for (int i = 1; i < fib.size(); ++i) {
		fib[i] = 1.0*(pow(log2(fib[i]+1), M_PI/2)*(M_PI/2*log2(fib[i-1]+1)))/1.0;
	}
	return fib;
}

std::vector<int> johnnyFibSequence2(int n, int offset, int multi) {
	std::vector<int> vec {1, 2};
	for (int i = 2; i < multi*log2(n); ++i) {
	    int p = vec[vec.size()-1];
	    int pp = vec[vec.size()-2];
	    vec.push_back(p+log2(n)*(i*exp(-M_PI)));
	}
	// do not want to add while building up the vector it will affect growth
	for (auto& ele : vec) {
		ele += offset;
	}
	return vec;
}



std::vector<int> temperatureSequence(int n) {
	std::vector<int> phase1;
	std::vector<int> phase2;
	std::vector<int> phase3;
	phase1 = johnnyFibSequence(n, 1);
	phase2 = johnnyFibSequence2(n, phase1.back(), 1);
	for (int i = log2(n); i >= 0; --i) {
	    phase3.push_back(i);
	}
	phase1.insert(phase1.end(), phase2.begin(), phase2.end());
	for (auto& ele : phase1) {
	    ele += log2(n/3)+1;
	}
	reverse(phase1.begin(), phase1.end());
	phase1.insert(phase1.end(), phase3.begin(), phase3.end());
	// it should be non-increasing order with last element being 0
	return phase1;
}

//.8
//.75
std::vector<int> dogeDoggoSequence(int n, double growth, int offset) {
	std::vector<int> res {1, 2};
	
	for (int i = 2; i < n; ++i) {
		res.push_back(pow(i*(.7*res[i-1]), growth)+i);
	}
	for (auto& ele : res) {
		ele += offset;
	}
	return res;
}

std::vector<int> temperatureSequence2(int n) {
	std::vector<int> phase1;
	std::vector<int> phase2;
	std::vector<int> phase3;
	int sz = log2(n);
	phase1 = dogeDoggoSequence(sz, .8, 0);
	phase2 = dogeDoggoSequence(sz, .75, phase1.back());
	for (int i = sz; i > 0; --i) {
	    phase3.push_back(i);
	}
	phase1.insert(phase1.end(), phase2.begin(), phase2.end());
	for (auto& ele : phase1) {
	    ele += log2(n/3)+1;
	}
	reverse(phase1.begin(), phase1.end());
	phase1.insert(phase1.end(), phase3.begin(), phase3.end());
	// it should be non-increasing order with last element being 0
	return phase1;	
}


/*
int main()
{
    int numVectors = 5;
	int lenVector = 5;
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
*/