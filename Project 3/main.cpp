#include "graph.h"
//#include "tests.h"
#include <iostream>
#define MANUAL_DRIVER 0
int main() {
	if (MANUAL_DRIVER) {
		Graph graph;

		for (int i =  0; i < 4; ++i) {
			graph.add_vertex();
		}
		graph.add_edge(1, 2);
		graph.add_edge(2, 3);
		graph.add_edge(3, 4);
		graph.add_edge(4, 1);

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

		Graph graph = create_barabasi_albert_graph(1000, 5);
		graph_to_file(&graph);
		generate_data();
		// Graph g;
		// g.add_vertex(); g.add_vertex();g.add_vertex(); g.add_vertex();
		// g.add_edge(1, 2);g.add_edge(3, 1); g.add_edge(4, 2);
		// //g.print_edges();

		// Graph g2 = g;
		// g2.add_vertex();

		// //g2.add_vertex(); g2.add_vertex();
		// //g2.add_edge(1, 2);


		// g.print_vertices();
		// g.print_edges();
		// std::cout << "----" << std::endl;
		// g2.print_vertices();
		// g2.print_edges();
		// std::cout << "----" << std::endl;
		// for (auto x : g.get_neighbors(1))
		// 	std::cout << x.get_m_id() << " ";
		// std::cout << std::endl;
		// generate_data();

	}
	
	return 0;
}