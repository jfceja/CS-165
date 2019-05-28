#include "graph.h"
#include <iostream>
#include <algorithm>

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
	: m_nodes(0) {

}

int Graph::get_num_nodes() {
	return m_nodes;
}

int Graph::get_num_edges() {
	int sum = 0;
	for (const auto& node : m_graph) {
		sum += node.second.get_children().size();
	}
	return sum/2;
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

void Graph::add_edge(int m_id_from, int m_id_to) {
	bool from_found = m_graph.find(m_id_from) == m_graph.end();
	bool to_found = m_graph.find(m_id_to) == m_graph.end();
	if (from_found || to_found) {
		std::cout << "From vertex or to vertex not found." << std::endl;
		return;
	}

	// undirected so add the id's to both vectors
	if (m_graph[m_id_from].edge_exists(m_id_to)) {
		std::cout << "Edge already exists." << std::endl;
	}
	m_graph[m_id_from].get_children().push_back(m_id_to);
	m_graph[m_id_to].get_children().push_back(m_id_from);
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

/*
	END GRAPH CLASS
*/