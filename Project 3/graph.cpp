#include "graph.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>

/*
	BEGIN NODE CLASS
*/
Node::Node() {
	this->m_id = -1;
}

Node::Node(int m_id) {
	this->m_id = m_id;
}

Node::Node(int m_id, std::vector<int> m_list) {
	this->m_id = m_id;
	this->m_list = m_list;
}

std::vector<int>& Node::get_children(){
	return m_list;
}

std::vector<int> Node::get_children() const {
	return m_list;
}

int Node::get_m_id() const {
	return this->m_id;
}

bool Node::edge_exists(int m_id) const {
	for (const auto& edge : m_list) {
		if (m_id == edge) {
			return true;
		}
	}
	return false;
}
/*
	END NODE CLASS
*/

/*
	BEGIN GRAPH CLASS
*/
Graph::Graph()
	: m_nodes(0)
	, m_edges(0) {

}

int Graph::get_num_nodes() {
	return m_nodes;
}

int Graph::get_num_edges() {
	return m_edges;
}

int Graph::get_degree() {
	// get_num_edges() is a given prototype so I can't modify it to make it const :P
	return m_edges*2;
}

int Graph::get_degree(int u) const {
	// using [] is not const as it can modify it
	if (m_graph.find(u) == m_graph.end()) {
		std::cout << "Given node to find degree does not exist." << std::endl;
		return 0;
	}
	return m_graph.find(u)->second.get_children().size();
}

bool Graph::is_neighbor(Node u, Node v) {
	// if it doesn't exist doing m_graphp[u] will then create it... let's prevent that.
	bool u_found = m_graph.find(u.get_m_id()) == m_graph.end();
	bool v_found = m_graph.find(v.get_m_id()) == m_graph.end();
	if (u_found || v_found) {
		return false;
	}
	const auto& u_list = m_graph[u.get_m_id()].get_children();
	return std::find(u_list.begin(), u_list.end(), v.get_m_id()) != u_list.end();
}

std::vector<Node> Graph::get_neighbors(Node u) {
	std::vector<Node> res;
	for (const auto& node_id : m_graph[u.get_m_id()].get_children()) {
		// constructor sets m_id and list vector
		Node current_node(node_id, m_graph[node_id].get_children());
		res.push_back(current_node);
	}
	return res;
}

void Graph::add_vertex() {
	// for now only allow id's in strictly increasing order :)
	Node node(m_nodes);
	m_graph[m_nodes++] = node;
}

bool Graph::add_edge(int m_id_from, int m_id_to) {
	bool from_found = m_graph.find(m_id_from) == m_graph.end();
	bool to_found = m_graph.find(m_id_to) == m_graph.end();
	if (from_found || to_found) {
		std::cout << "From vertex or to vertex not found." << std::endl;
		return false;
	}

	// undirected so add the id's to both vectors
	if (m_graph[m_id_from].edge_exists(m_id_to)) {
		std::cout << "Edge already exists." << std::endl;
		return false;
	}
	m_graph[m_id_from].get_children().push_back(m_id_to);
	m_graph[m_id_to].get_children().push_back(m_id_from);
	++m_edges;
	return true;
}

void Graph::print_vertices() const {
	for (const auto& node : m_graph) {
		std::cout << node.first << std::endl;
	}
}

void Graph::print_edges() const {
	for (const auto& node : m_graph) {
		for (const auto& m_id : node.second.get_children()) {
			std::cout << "Vertex " << node.second.get_m_id() << " -> " << m_id << std::endl;
		}
	}
}

void Graph::generate_file() {
	std::string filename_vertices = "inputVertices.csv";
	std::string filename_edges = "edgesVertices.csv";
	create_empty_timings_file(filename_vertices, true);
	for (const auto& node : m_graph) {
		add_timings_to_file(node.first, node.first, filename_vertices, true);
	}

	create_empty_timings_file(filename_edges, false);
	for (const auto& node : m_graph) {
		for (const auto& child : node.second.get_children()) {
			add_timings_to_file(node.first, child, filename_edges, false);
		}
	}
}

void Graph::create_empty_timings_file(std::string filename, bool vertex) {
	std::ofstream f;
	f.open(filename, std::ios::trunc);
	if (vertex) {
		f << "Id,Label,time\n";
	} else {
		f << "Source,Target,Type,Id,Label,timeset,Weight\n";
	}
	f.close();
}

void Graph::add_timings_to_file(int from, int to, std::string filename, bool vertex) {
	std::ofstream f;
	f.open(filename, std::ios::app);
	if (vertex) {
		f << from << "," << from << ",\n";
	} else {
		f << from << "," << to << "," << "undirected" << ",,,,\n";
	}
	f.close();
}

// code slowly going down the drain with these design decisions
Diameter_result Graph::get_eccentricity(int from) const {
	std::unordered_set<int> seen;
	std::queue<int> q;
	int distnace = -1;
	int node = 0;
	q.push(from);
	seen.insert(from);

	while (!q.empty()) {
		std::vector<int> node_list;
		int recent_node;
		while(!q.empty()) {
			node_list.push_back(q.front());
			q.pop();	
		}
		for (const auto& current : node_list) {
			for (auto& neighbor : m_graph.find(current)->second.get_children()) {
			if (seen.find(neighbor) == seen.end()) {
					recent_node = neighbor;
					seen.insert(neighbor);
					q.push(neighbor);
				}
			}
		}
		++distnace;
		node = recent_node;
	}
	return Diameter_result{from, node, distnace};
}

// this can be const but whatever
int Graph::get_triangles() {
	int cnt = 0;
	for (const auto& node : m_graph) {
		std::vector<Node> neighbors = get_neighbors(node.second.get_m_id());
		for (unsigned int i = 0; i < neighbors.size(); ++i) {
			for (unsigned int j = i+1; j < neighbors.size(); ++j) {
				int deg_v = get_degree(node.second.get_m_id());
				Node& left = neighbors[i];
				int left_deg = get_degree(left.get_m_id());
				Node& right = neighbors[j];
				int right_deg = get_degree(right.get_m_id());
				// using pseudocode from Stanford CS 167 paper http://theory.stanford.edu/~tim/s14/l/l1.pdf 
				// if both neighbors of v have higher degree than v or equal but higher lexicographically for individual ties
				if ((left_deg > deg_v && right_deg > deg_v)
					|| (left_deg > deg_v && right_deg == deg_v && right.get_m_id() > node.second.get_m_id())
					|| (right_deg > deg_v && left_deg == deg_v && left.get_m_id() > node.second.get_m_id())) {
					if (left.edge_exists(right.get_m_id())) {
						++cnt;
					}
				}
				
			}
		}
	}
	return cnt;
}

int Graph::two_edge_path(int m_id) const {
	int deg = get_degree(m_id);
	return deg * (deg - 1) / 2;
}

int Graph::total_two_edge_path() const {
	int total = 0;
	for (const auto& node : m_graph) {
		total += two_edge_path(node.second.get_m_id());
	}
	return total;
}

std::map<int, int> Graph::vertex_to_degree_map() const {
	std::map<int, int> mapping;
	for (const auto& node : m_graph) {
		mapping[node.second.get_m_id()] = get_degree(node.second.get_m_id());
	}
	return mapping;
}
/*
	END GRAPH CLASS
*/