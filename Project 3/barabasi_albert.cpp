#include "graph.h"
#include <random>
#include <chrono>
#include <iostream>

bool bernoulli_prob(double prob, std::mt19937& rng) {
	std::bernoulli_distribution gen(prob);
	return gen(rng);
}

void iterate_previous(int m_id, std::mt19937& rng, int d, int& num_added, Graph& g) {
	for (int node_consider = 0; node_consider < m_id; ++node_consider) {
		if (num_added >= d) {
			break;
		}
		double prob = g.get_degree(node_consider);
		prob /= g.get_degree();
		bool add_edge = bernoulli_prob(prob, rng);
		if (add_edge) {
			if (g.add_edge(m_id, node_consider)) {
				++num_added;
			}
		}
	}
}

Graph create_barabasi_albert_graph(int n, int d) {
	Graph g;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng = std::mt19937(19937);
	g.add_vertex(); // 0
	g.add_vertex(); // 1
	g.add_edge(0, 1);

	for (int node = 0; node < n; ++node) {
		int m_id = node + 2;
		int num_vertices = g.get_num_nodes();
		g.add_vertex();
		int num_added = 0;
		for (int deg = 0; deg < d; ++deg) {
			// iterate through all previous nodes
			iterate_previous(m_id, rng, d, num_added, g);	
		}
		// guarantees precisely d vertices being initially added, no more no less.
		// while (num_added < d && num_added < num_vertices) {
		// 	iterate_previous(m_id, rng, d, num_added, g);
		// }
	}
	return g;
}