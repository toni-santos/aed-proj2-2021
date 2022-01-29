#ifndef AED_PROJ2_2021_GRAPH_H
#define AED_PROJ2_2021_GRAPH_H

class Graph;
struct Edge;
struct Node;

#include "Stop.h"
#include "filters.h"
#include "minHeap.h"

#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <vector>

#define INF (std::numeric_limits<double>::max() / 2)

struct Edge {
    std::string dest; // Destination node
    double distance;  // Weight
    std::string code; // Code of the Line
};

struct Node {
    std::deque<Edge> adj{}; // The list of outgoing edges (to adjacent nodes)
    bool visited{false};
    double dist{};
    std::string pred{};
    std::string line{};
    Stop stop{};

    Node(Stop stop) : stop(stop) {}
    Node() {}
};

class Graph {
    int n;       // Graph size (vertices are numbered from 1 to n)
    bool hasDir; // false: undirected; true: directed
    // std::vector<Node> nodes; // The list of nodes being represented
    std::unordered_map<std::string, Node> nodes;

    void addFootEdges();

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int num, bool dir = false);
    Graph(){};
    // Add edge from source to destination with a certain weight fred
    void addEdge(const std::string &src, const std::string &dest,
                 const std::string &code, const double &distance = 1.0);
    void addEdge(Node &src, Node &dest, const std::string &code,
                 const double &distance = 1.0);

    // std::vector<Node> getNodes() { return nodes; };
    std::unordered_map<std::string, Node> &getNodes() { return nodes; };
    Node &getNode(const std::string &id) { return nodes.at(id); };

    void setStart(const double &lat, const double &lon);
    void setEnd(const double &lat, const double &lon);

    void readStops();
    void readLines();
    // int findNodeIdx(std::string code);
    void populate();

    void dijkstra(const std::string &src, const std::string &dest,
                  const filter &f);
    // int dijkstraDistance(const std::string &a, const std::string &b);
    std::list<Node> dijkstraPath(const std::string &src,
                                 const std::string &dest, const filter &f);

    void dijkstraCost(const std::string &src, const std::string &dest,
                      const filter &f);
    std::list<Node> dijkstraCostPath(const std::string &src,
                                     const std::string &dest, const filter &f);

    void dijkstraLines(const std::string &src, const std::string &dest,
                       const filter &f);
    std::list<Node> dijkstraLinesPath(const std::string &src,
                                      const std::string &dest, const filter &f);

    void bfs(const std::string &src, const std::string &dest, const filter &f);
    std::list<Node> bfsPath(const std::string &src, const std::string &dest,
                            const filter &f);
};

#endif
