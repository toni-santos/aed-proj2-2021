#include <fstream>
#include <filesystem>
#include <algorithm>

#include "../includes/graph.h"
#include "../includes/constants.h"
#include "../includes/Utils.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num) {}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int& dest, std::string& code, int distance) {
	/*
		if (src<1 || src>n || dest<1 || dest>n) return;
		nodes[src].adj.push_back({dest, distance});
		if (!hasDir) nodes[dest].adj.push_back({src, distance});
    */
}

void Graph::readStops() {
	std::ifstream stopsFile {STOPS_FILE_PATH};

	if (stopsFile.fail()) return;

	std::string line;
	std::vector<Node> nods;

	getline(stopsFile,line);

	while (!stopsFile.eof()) {
		std::vector<std::string> parsedLine;
		getline(stopsFile, line);
		if (line.empty()) continue;

		parsedLine = split(line, ',');

		Stop stop = Stop(parsedLine.at(0), parsedLine.at(1), parsedLine.at(2), stod(parsedLine.at(3)), stod(parsedLine.at(4)));
		Node node {std::list<Edge>(), false, stop};
		nods.push_back(node);
	}

	stopsFile.close();

	this->nodes = nods;
}


void Graph::readLines() {
	for (auto& file: std::filesystem::directory_iterator{LINE_FOLDER_PATH}) {
		std::ifstream f{file.path()};

		std::string lineCode = split(file.path(), '_').at(1);

		if (f.fail()) continue;
		std::string line;

		getline(f, line);
		if (line == "0") {
			f.close();
			continue;
		}

		while (f.good()) {
			getline(f, line);
			if (line.empty()) continue;
			std::string stopCode1 = line;
			Node n1 = nodes.at(findNodeIdx(stopCode1));

			getline(f, line);
			if (line.empty()) continue;
			std::string stopCode2 = line;
			Node n2 = nodes.at(findNodeIdx(stopCode2));

			double dist = haversine(n1.stop.getLatitude(), n1.stop.getLongitude(), n2.stop.getLatitude(), n2.stop.getLongitude());
		}

		f.close();
	}

}

void Graph::print() {
	for (auto e: nodes) {
		std::cout << e.stop.getName() << " " << e.stop.getCode() << " " << e.stop.getZone() << " " << e.stop.getLatitude() << " " << e.stop.getLongitude() << '\n' << std::flush;
	}
/*
	for (auto line: this->lines) {
		std::cout << line.code << " " << line.name << '\n' << std::flush;
	}*/
}

int Graph::findNodeIdx(std::string code) {
	auto itr = std::find_if(nodes.cbegin(), nodes.cend(), [code](Node& n1){
		return n1.stop.getCode() == code;
	});

	if (itr != nodes.cend()) {
		return  std::distance(nodes.cbegin(), itr);
	} else {
		return -1;
	}
}




