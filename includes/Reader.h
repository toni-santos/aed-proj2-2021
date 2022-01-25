//
// Created by toni on 25/01/22.
//

#ifndef AED_PROJ2_2021_READER_H
#define AED_PROJ2_2021_READER_H


#include <string>
#include <vector>

struct Stop {
	std::string code;
	std::string name;
	std::string zone;
	double latitude;
	double longitude;

};

struct Line {
	std::string code;
	std::string name;
};

class Reader {
	std::vector<Stop> stops;
	std::vector<Line> lines;
public:
	void readStops();
	void readLines();
	void print();
};


#endif //AED_PROJ2_2021_READER_H
