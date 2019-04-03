#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>

/* 
	in-place
	passing vector by copy, so start of timer should start inside this function
*/
std::chrono::milliseconds bubbleSort (std::vector<int>  arr) {
	auto beginTime = std::chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < arr.size(); ++i) {
		for (unsigned int j = 1; j < arr.size()-i; ++j) {
			if (arr[j-1] > arr[j]) {
				std::swap(arr[j-1], arr[j]);
			}
		}
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
}

/*
	in-place
	passing vector by copy, so start of timer should start inside this function
*/
std::chrono::milliseconds insertionSort(std::vector<int> arr) {
	auto beginTime = std::chrono::high_resolution_clock::now();
	for (unsigned int i = 1; i < arr.size(); ++i) {
		int temp = arr[i];
		
		// slide elements down to make room for a[i]
		int j = i;
		while (j > 0 && arr[j-1] > temp) {
			arr[j] = arr[j-1];
			--j;
		}
		arr[j] = temp;
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime);
}

void printArray(const std::vector<int>& arr) {
	for (unsigned int i = 0; i < arr.size(); ++i) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main() {
	int sz = 10000;
	std::vector<int> arr;
	for (int i = sz-1; i >= 0; --i) {
		arr.push_back(i);
	}
	
	// printArray(arr, sz);
	std::cout << "Bubble sort took " << bubbleSort(arr).count() << " milliseconds" << std::endl;
	
	std::cout << "Insertion sort took " << insertionSort(arr).count() << " milliseconds" << std::endl;
	
	std::cout << "Running std::sort()" << std::endl;
	std::sort(arr.begin(), arr.end());
	std::cout << "Finished std::sort()" << std::endl;
	
	//printArray(arr, sz);
}