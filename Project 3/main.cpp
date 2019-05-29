#include "graph.h"
#include <iostream>
#define MANUAL_DRIVER 0
int main() {
	if (MANUAL_DRIVER) {
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
	} else {
		/*
			questions:
				does d in barabasi mean at least, at most or precisely or something else edges being added?
				does n mean total number or vertices in graph or nodes ADDED given inital 2 vertces graph?
					if former, what if n == 1?
 		*/
		// Graph graph = create_barabasi_albert_graph(1000, 5);
		// graph.generate_file();

		// testing diameter
		// Graph graph;
		// for (int i = 0; i < 8; ++i) {
		// 	graph.add_vertex();
		// }
		// graph.add_edge(0, 1);
		// graph.add_edge(1, 2); graph.add_edge(1, 3); graph.add_edge(1, 7);
		// graph.add_edge(2, 3); graph.add_edge(2, 4);
		// graph.add_edge(3, 4);
		// graph.add_edge(2, 5); graph.add_edge(5, 6); graph.add_edge(6, 7);
		//graph.print_edges();


		// testing triangles
		// Graph graph;
		// for (int i = 0; i < 5; ++i) {
		// 	graph.add_vertex();
		// }
		// graph.add_edge(0, 1);
		// graph.add_edge(0, 2);
		// graph.add_edge(1, 2);
		// graph.add_edge(2, 3);
		// graph.add_edge(2, 4);

		// // should be 0.375
		// std::cout << get_clustering_coefficient(graph) << std::endl;
		// for (const auto& x : get_degree_distribution(graph)) {
		// 	std::cout << x.first << "->" << x.second << std::endl;
		// }


		Graph graph = create_barabasi_albert_graph(10000, 5);
		graph.generate_file();
		std::cout << "Graph craeted." << std::endl;
		std::cout << "diameter: " << get_diameter(graph) << std::endl;
		std::cout << "get_clustering_coefficient: " << get_clustering_coefficient(graph) << std::endl;
		std::cout << "---------------" << std::endl;
		for (const auto& x : get_degree_distribution(graph)) {
			std::cout << x.first << "->" << x.second << std::endl;
		}

	}
	
	return 0;
}