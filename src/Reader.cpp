//
// Created by toni on 25/01/22.
//

#include "../includes/Reader.h"
#include "../includes/constants.h"
#include "../includes/Utils.h"

#include <iostream>
#include <fstream>
#include <vector>

void Reader::readStops() {
	std::ifstream stopsFile {STOPS_FILE_PATH};

	if (stopsFile.fail()) return;

	std::string line;

	getline(stopsFile,line);

	while (!stopsFile.eof()) {
		Stop stop;
		std::vector<std::string> parsedLine;
		getline(stopsFile, line);
		if (line.empty()) continue;

		parsedLine = split(line, ',');

		stop.code = parsedLine.at(0);
		stop.name = parsedLine.at(1);
		stop.zone = parsedLine.at(2);
		stop.latitude = stod(parsedLine.at(3));
		stop.longitude = stod(parsedLine.at(4));

		this->stops.push_back(stop);
	}

	stopsFile.close();
}

void Reader::readLines() {
	std::ifstream linesFile {LINES_FILE_PATH};

	if (linesFile.fail()) return;

	std::string line;

	getline(linesFile, line);

	while(linesFile.good()) {
		Line busline;
		std::vector<std::string> parsedLine;
		getline(linesFile, line);
		if (line.empty()) continue;

		parsedLine = split(line, ',');

		busline.code = parsedLine.at(0);
		busline.name = parsedLine.at(1);

		this->lines.push_back(busline);

	}

	linesFile.close();
}

void Reader::print() {
	for (auto stop: this->stops) {
		std::cout << stop.name << " " << stop.code << " " << stop.zone << " " << stop.latitude << " " << stop.longitude << '\n' << std::flush;
	}

	for (auto line: this->lines) {
		std::cout << line.code << " " << line.name << '\n' << std::flush;
	}
}