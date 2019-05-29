#include "project3.h"
#include "node.h"
#include <string>
#include <unordered_map>

struct Diameter_result {
	int from;
	int to;
	int result;
};

class Graph : public AbstractGraph {
public:
	Graph();

	int get_num_nodes();

	int get_num_edges();

	int get_degree();

	int get_degree(int u) const;

	bool is_neighbor(Node u, Node v);

	void add_vertex();

	bool add_edge(int m_id_from, int m_id_to);

	std::vector<Node> get_neighbors(Node u);

	void generate_file();

	void print_vertices() const;

	void print_edges() const;

	Diameter_result get_eccentricity(int from) const;

	int get_triangles();

	int two_edge_path(int m_id) const;

	int total_two_edge_path() const;

	std::map<int, int> vertex_to_degree_map() const;
private:
	int m_nodes;

	int m_edges;

	std::unordered_map<int, Node> m_graph;

	void create_empty_timings_file(std::string filename, bool vertex);

	void add_timings_to_file(int from, int to, std::string filename, bool vertex);
};