#include <algorithm>
#include <filesystem>
#include <fstream>

#include "../includes/Utils.h"
#include "../includes/constants.h"
#include "../includes/graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num) {
    readStops();
    readLines();
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(Node &src, Node &dest, const std::string &code,
                    const double &distance) {
    src.adj.push_back({dest.stop.getCode(), distance, code});
    if (!hasDir)
        dest.adj.push_back({src.stop.getCode(), distance, code});
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(const std::string &src, const std::string &dest,
                    const std::string &code, const double &distance) {
    addEdge(nodes[src], nodes[dest], code, distance);
}

void Graph::readStops() {
    std::ifstream stopsFile{STOPS_FILE_PATH};

    if (stopsFile.fail())
        return;

    std::string line;

    getline(stopsFile, line);

    while (!stopsFile.eof()) {
        std::vector<std::string> parsedLine;
        getline(stopsFile, line);
        if (line.empty())
            continue;

        parsedLine = split(line, ',');

        Stop stop = Stop(parsedLine.at(1), parsedLine.at(0), parsedLine.at(2),
                         stod(parsedLine.at(4)), stod(parsedLine.at(3)));
        Node node{stop};
        nodes.emplace(stop.getCode(), node);
    }

    stopsFile.close();
}

void Graph::readLines() {
    for (auto &file : std::filesystem::directory_iterator{LINE_FOLDER_PATH}) {
        std::ifstream f{file.path()};

        std::string lineCode = split(file.path().generic_string(), '_').at(1);

        if (f.fail())
            continue;

        std::string stops;
        getline(f, stops);
        int nstops = std::stoi(stops);

        std::string stop;
        Node current;
        Node last;

        for (int i{0}; i < nstops; ++i) {
            getline(f, stop);
            current = getNode(stop);

            if (i > 0) {
                double dist = haversine(
                    current.stop.getLatitude(), current.stop.getLongitude(),
                    last.stop.getLatitude(), last.stop.getLongitude());

                addEdge(last, current, lineCode, dist);
            }

            last = current;
        }

        f.close();
    }
}

void Graph::populate() {
    readStops();
    readLines();
}

void Graph::dijkstra(const std::string &s) {
    MinHeap<std::string, double> q(n, "");

    for (auto i{nodes.begin()}, end{nodes.end()}; i != end; ++i) {
        i->second.dist = INF;
        q.insert(i->first, INF);
        i->second.visited = false;
    }

    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;

    while (q.getSize() > 0) {
        std::string uc = q.removeMin();
        Node u = getNode(uc);
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        u.visited = true;
        for (auto e : u.adj) {
            std::string vc = e.dest;
            Node v = getNode(vc);
            int w = u.dist + e.distance;
            if (!v.visited && w < v.dist) {
                v.dist = w;
                q.decreaseKey(vc, v.dist);
                v.pred = uc;
            }
        }
    }
}

int Graph::dijkstra_distance(const std::string &a, const std::string &b) {
    dijkstra(a);
    if (nodes[b].dist == INF)
        return -1;
    return nodes[b].dist;
}

auto Graph::dijkstra_path(const std::string &a, const std::string &b)
    -> std::list<Node> {
    dijkstra(a);
    std::list<Node> path;
    if (nodes[b].dist == INF)
        return path;
    path.push_back(getNode(b));
    std::string v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(getNode(v));
    }
    return path;
}
