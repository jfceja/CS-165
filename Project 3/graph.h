#include "project3.h"
#include "node.h"
#include <unordered_map>

class Graph : public AbstractGraph {
public:
	Graph();

	int get_num_nodes();

	int get_num_edges();

	bool is_neighbor(Node u, Node v);

	void add_vertex();

	void add_edge(int m_id_from, int m_id_to);

	std::vector<Node> get_neighbors(Node u);


	/*
	just debugging functions
	*/
	void print_vertices() const;

	void print_edges() const;

private:

	int m_nodes;

	std::unordered_map<int, Node> m_graph;
};