#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <math.h>
#include "project1.h"
#include "rng.h"

using namespace std;
enum Sorts {
	annealingSort,
	bubbleSort,
	insertionSort,
	shellSort,
	spinTheBottleSort,
	introSort
};
struct timing 
{
    int n;
    double seconds;
};

// get a vector of ints in 1, 2, ... , n shuffled randomly
vector<int> get_random_shuffled_int_vector(int n)
{
    vector<int> vec = vector<int>(n);
    for(int i = 0; i < n; i++)
        vec[i] = (i + 1);
    random_shuffle(vec.begin(), vec.end());
    return vec;
}

// run and time sort for vector with n elements. return vector of timings with sizes and seconds
timing time_sort(std::vector<int>& vec, int reps, Sorts sortPtr, bool partial, std::mt19937& rng)
{
    double total_time = 0.0;
    for(int i = 0; i < reps; i++)
    {
		std::vector<int> copy = vec;
		
		std::vector<int> temps = temperatureSequence(vec.size());
		std::vector<int> seq;
		if (sortPtr == Sorts::annealingSort) {
			seq = johnnyFibSequence(vec.size(), ceil(temps.size()/log2(vec.size()));
		}
		else {
			seq = johnnyFibSequence(vec.size(), 1);
		}
		= johnnyFibSequence(vec.size());
		if (partial) {
			partial_shuffle_vector(copy, rng);
		}
		else {
			shuffle_vector(copy, rng);
		}
        clock_t c_start = clock();
		switch(sortPtr) {
			case Sorts::annealingSort:
				//annealing_sort
				annealing_sort(copy, temps, seq);
				break;
			case Sorts::bubbleSort:
				bubble_sort(copy);
				break;
			case Sorts::insertionSort:
				insertion_sort(copy);
				break;
			case Sorts::shellSort:
				shell_sort(copy, seq);
				break;
			case Sorts::spinTheBottleSort:
				spin_the_bottle_sort(copy);
				break;
			default:
				std::sort(copy.begin(), copy.end());
				break;
				
		}
        //sort(rvec.begin(), rvec.end());
        clock_t c_end = clock();
        total_time += (float)(c_end - c_start) / CLOCKS_PER_SEC;
		if (!is_sorted(copy.begin(), copy.end())) {
			std::cout << "ERROR: VECTOR NOT SORTED!\n";
		}
    }
    timing t;
    t.n = vec.size();
    t.seconds = (float)total_time/reps;
	
    return t;
}

// create/truncate a file with chosen filename. insert csv header "funcname,n,seconds"
void create_empty_timings_file(string filename)
{
    ofstream f;
    f.open(filename, ios::trunc);
    f << "funcname,n,seconds\n";
    f.close();
}

// append timings data in csv format to a file with no header. (header should be created first)
void add_timings_to_file(string funcname, timing t, string filename)
{
    ofstream f;
    f.open(filename, ios::app);
    f << funcname << "," << t.n << "," << t.seconds << "\n";
    f.close();
}

/*
	Since the programs are going to be ran on openlab or some shared server, I cannot run all of the tests as one big program.
	I anticipate the sorting for each algorithm to take roughly 5-8 hours so doing that for all 5 algorithms would now work
	because I think the servers will be restarted before it finished.
	My work-around is to collect the data for each algorithm independently and merge the results.
*/


int main()
{	
    create_empty_timings_file("timings.csv");
    timing t;
	//std::cout << "1.0\n";
	Sorts currentAlgo = Sorts::annealingSort;
	bool partial = false;
	std::string sort[] = {"Annealing sort", "Bubble sort", "Insertion sort", "Shell sort_v2", "Spin the bottle sort", "Introsort"};
	vector<int> elementsBound = {1000, 			2000000, 			2000000,	 2000000, 			250000, 			100000000};
	
	int seed;
	std::mt19937 rng = std::mt19937 (seed = time(0));
	std::cout << "Seed = " << seed << std::endl;
	std::cout << "SORTING WITH " << sort[currentAlgo] << "!\n";
	
    for(int n = 10; n <= elementsBound[currentAlgo]/* 10000000 */; n *= 2)
    {
		std::cout << "Sorting with " << n << " elements.\n";
		std::string filename = sort[currentAlgo];
		std::vector<int> vec = getVector(n);
		if (partial) {
			filename += "_partially_sorted";
			//partial_shuffle_vector(vec, rng);
		}
		else {
			//shuffle_vector(vec, rng);
		}
        t = time_sort(vec, 3, currentAlgo, partial, rng);
		filename += ".csv";
        add_timings_to_file(sort[currentAlgo], t, filename);
    }
}