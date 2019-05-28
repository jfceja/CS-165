#include <vector>
#include <map>

#ifndef PROJECT3_H
#define PROJECT3_H

/******* NODE CLASS ********/
class Node;  // define/implement in node.h

/******* GRAPH BASE CLASS TO OVERRIDE********/
class AbstractGraph 
{
    public: // all methods must be overriden
        virtual int get_num_nodes() = 0; // number of nodes
        virtual int get_num_edges() = 0; // number of edges
        virtual bool is_neighbor(Node u, Node v) = 0 ;
        virtual std::vector<Node> get_neighbors(Node u) = 0; 
};

class Graph; // define interface in graph.h, implement in graph.cpp (see below)
             // should #include "node.h"

/* graph.h
class Graph : public AbstractGraph
{
    ... // list all methods to override
    ... // list any other constructors, members, and member functions you may want to use
}
*/

/* graph.cpp
// implement all of your members declared in graph.h
...
bool Graph::is_neighbor(Node u, Node v) 
{
    ...
}
...
*/

/******* ALGORITHMS TO IMPLEMENT ********/
// implement all 3 in graph_algorithms.cpp
// should include graph.h
int get_diameter(Graph graph); 
float get_clustering_coefficient(Graph graph);
std::map<int, int> get_degree_distribution(Graph graph);

/******* GRAPH GENERATION FUNCTIONS ********/
Graph create_erdos_renyi_graph(int n, float p); // implement in erdos_renyi.cpp
                                                // only if your student ID is ODD
Graph create_barabasi_albert_graph(int n, int d); // implement in barabasi_albert.cpp
                                                  // only if your student ID is EVEN
// whichever file you have should #include "graph.h"

/******* FILE SUMMARY (SORTED BY DEPENDENCIES) 
    project3.h
    node.h
    graph.h
    graph.cpp
    graph_algorithms.cpp
    erdos_renyi.cpp OR barabasi_albert.cpp (see GRAPH GENERATION FUNCTIONS section)
    run.sh 
*/
#endif