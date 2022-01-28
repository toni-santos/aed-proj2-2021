#ifndef AED_PROJ2_2021_GRAPH_H
#define AED_PROJ2_2021_GRAPH_H

class Graph;

#include "Stop.h"
#include "minHeap.h"

#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

#define INF (std::numeric_limits<double>::max() / 2)

class Graph {
    struct Edge {
        std::string dest; // Destination node
        double distance;  // Weight
        std::string code; // Code of the Line
    };

    struct Node {
        std::deque<Edge>
            adj{}; // The list of outgoing edges (to adjacent nodes)
        bool visited{false};
        double dist{};
        std::string pred{};
        Stop stop{};

        Node(Stop stop) : stop(stop) {}
        Node() {}
    };

    int n;       // Graph size (vertices are numbered from 1 to n)
    bool hasDir; // false: undirect; true: directed
    // std::vector<Node> nodes; // The list of nodes being represented
    std::unordered_map<std::string, Node> nodes;
    void dijkstra(const std::string &s);
    int dijkstra_distance(const std::string &a, const std::string &b);
    std::list<Node> dijkstra_path(const std::string &a, const std::string &b);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int num, bool dir = false);
    Graph(){};
    // Add edge from source to destination with a certain weight
    void addEdge(const std::string &src, const std::string &dest,
                 const std::string &code, const double &distance = 1.0);
    void addEdge(Node &src, Node &dest, const std::string &code,
                 const double &distance = 1.0);

    // std::vector<Node> getNodes() { return nodes; };
    std::unordered_map<std::string, Node> getNodes() { return nodes; };
    Node getNode(const std::string &id) const { return nodes.at(id); };

    void readStops();
    void readLines();
    // int findNodeIdx(std::string code);
    void populate();
};

#endif
