#ifndef AED_PROJ2_2021_STOP_H
#define AED_PROJ2_2021_STOP_H


#include <string>

class Stop {
	std::string name, code, zone;
	double longitude, latitude;

public:
	Stop(): name(""), code(""), zone(""), latitude(0), longitude(0) {};

	Stop(std::string name, std::string code, std::string zone, double longitude, double latitude):
		name(name), code(code), zone(zone), longitude(longitude), latitude(latitude) { };

	std::string getName() { return this->name; }
	std::string getCode() { return this->code; }
	std::string getZone() { return this->zone; }
	double getLongitude() { return this->longitude; }
	double getLatitude() { return this->latitude; }
};


#endif //AED_PROJ2_2021_STOP_H
