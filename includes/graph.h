#ifndef AED_PROJ2_2021_GRAPH_H
#define AED_PROJ2_2021_GRAPH_H

//#include "minHeap.h"
#include "Stop.h"

#include <vector>
#include <list>
#include <iostream>

class Graph {
    struct Edge {
		int src;				// Source node
        int dest;   			// Destination node
		double distance; 		// Weight
		std::string code; 		// Code of the Line
    };

    struct Node {
        std::list<Edge> adj; 	// The list of outgoing edges (to adjacent nodes)
        bool visited;
		Stop stop;
    };

    int n;              		// Graph size (vertices are numbered from 1 to n)
    bool hasDir;        		// false: undirect; true: directed
    std::vector<Node> nodes;	// The list of nodes being represented
public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int num, bool dir = false);
	Graph() {};
    // Add edge from source to destination with a certain weight
    void addEdge(int& src, int& dest, std::string& code, double distance = 1.0);

	std::vector<Node> getNodes() { return nodes; };

	void readStops();
	void readLines();
	void print();
	int findNodeIdx(std::string code);
	void populate();
};



#endif
