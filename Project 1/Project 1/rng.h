#include <vector>
#include <random>
#include <ctime>

void shuffle_vector(std::vector<int>& nums, std::mt19937& rng);

std::vector<int> getVector(const int& n);

std::vector<std::vector<int>> randomVectors(const int& numVectors, const int& lenVector, int seed);

void partial_shuffle_vector(std::vector<int>& nums, std::mt19937& rng);

std::vector<int> bestGapSequence();

std::vector<int> johnnyFibSequence(int n, int multi);
std::vector<int> johnnyFibSequence2(int n, int offset, int multi);
std::vector<int> temperatureSequence(int n);

std::vector<int> temperatureSequence2(int n);
std::vector<int> dogeDoggoSequence(int n, double growth, int offset);