#ifndef _GRAPH_H_
#define _GRAPH_H_

//#include "minHeap.h"
#include "Stop.h"

#include <vector>
#include <list>
#include <iostream>

class Graph {
    struct Edge {
		// int src				// Source node
        int dest;   			// Destination node
        int distance; 			// An integer weight
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

    // Add edge from source to destination with a certain weight
    void addEdge(int& dest, std::string& code, int distance = 1);

	std::vector<Node> getNodes() { return nodes; };

	void readStops();
	void readLines();
	void print();
	int findNodeIdx(std::string code);
};



#endif
