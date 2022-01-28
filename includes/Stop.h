#ifndef AED_PROJ2_2021_STOP_H
#define AED_PROJ2_2021_STOP_H

class Stop;

#include <string>

class Stop {
    std::string name, code, zone;
    double longitude, latitude;

public:
    Stop() : name(""), code(""), zone(""), latitude(0), longitude(0){};

    Stop(std::string name, std::string code, std::string zone, double longitude,
         double latitude)
        : name(name), code(code), zone(zone), longitude(longitude),
          latitude(latitude){};

    std::string getName() const { return this->name; }
    std::string getCode() const { return this->code; }
    std::string getZone() const { return this->zone; }
    double getLongitude() const { return this->longitude; }
    double getLatitude() const { return this->latitude; }
};

#endif // AED_PROJ2_2021_STOP_H
