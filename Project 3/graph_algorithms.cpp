#include "graph.h"
#include <random>
#include <chrono>

int get_diameter(Graph graph) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng = std::mt19937(19937);
	std::uniform_int_distribution<int> dist(0, graph.get_num_nodes() - 1);

	int Dmax = 0;
	Diameter_result ecce =  graph.get_eccentricity(dist(rng));

	while (ecce.result > Dmax) {
		Dmax = ecce.result;
		ecce = graph.get_eccentricity(ecce.to);
	}
	return Dmax;
}

float get_clustering_coefficient(Graph graph) {
	return static_cast<float>(3 * graph.get_triangles())/graph.total_two_edge_path();
}

std::map<int, int> get_degree_distribution(Graph graph) {
	// vertex to degree mapping, we cant degree to vertex so just reverse
	std::map<int, int> pre_process = graph.vertex_to_degree_map();
	std::map<int, int> post_process;
	for (std::map<int, int>::iterator itr = pre_process.begin(); itr != pre_process.end(); ++itr) {
		post_process[itr->second]++;
	}
	return post_process;
}