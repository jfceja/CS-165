#include "graph.h"
#include <iostream>

int main() {
	Graph graph;

	for (int i =  0; i < 4; ++i) {
		graph.add_vertex();
	}
	graph.add_edge(0, 1);
	graph.add_edge(1, 2);
	graph.add_edge(2, 3);
	graph.add_edge(3, 0);

	graph.print_vertices();
	graph.print_edges();
	Node node10(10);
	Node node2(2);
	Node node0(0);
	Node node3(3);
	std::cout << "Number of nodes " <<  graph.get_num_nodes() << std::endl;
	std::cout << "Number of edges " << graph.get_num_edges() << std::endl;
	std::cout << graph.is_neighbor(node2, node0) << std::endl;
	std::cout << "Neighbors of neighbor of node 3... " << std::endl;
	for (auto x : graph.get_neighbors(node3)) {
		/*
			node 3 expected output:
			0:
				1
				3
			2:
				1
				3
		*/
		std::cout << x.get_m_id() << ":" << std::endl;
		for (auto neigh : x.get_children()) {
			std::cout << "\t" << neigh << std::endl;
		}
		
	}

	return 0;
}