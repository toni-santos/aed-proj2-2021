#ifndef AED_PROJ2_2021_STOP_H
#define AED_PROJ2_2021_STOP_H

class Stop;

#include <string>

/**
 * @brief Represents a stop for a public transport network.
 */
class Stop {
    /**
     * @brief This stop's name.
     */
    std::string name;
    /**
     * @brief This stop's code.
     */
    std::string code;
    /**
     * @brief This stop's zone.
     */
    std::string zone;
    /**
     * @brief This stop's latitude.
     */
    double latitude;
    /**
     * @brief This stop's longitude.
     */
    double longitude;

public:
    /**
     * @brief Default constructor.
     */
    Stop() : name(""), code(""), zone(""), latitude(0), longitude(0){};

    /**
     * @brief Creates a new stop with the specified values.
     *
     * @param name The stop's name.
     * @param code The stop's code.
     * @param zone The stop's zone.
     * @param latitude The stop's latitude.
     * @param longitude The stop's longitude.
     */
    Stop(const std::string &name, const std::string &code,
         const std::string &zone, const double &latitude,
         const double &longitude)
        : name(name), code(code), zone(zone), longitude(longitude),
          latitude(latitude){};

    /**
     * @return This stop's name.
     */
    std::string getName() const { return this->name; }
    /**
     * @return This stop's code.
     */
    std::string getCode() const { return this->code; }
    /**
     * @return This stop's zone.
     */
    std::string getZone() const { return this->zone; }
    /**
     * @return This stop's latitude.
     */
    double getLatitude() const { return this->latitude; }
    /**
     * @return This stop's longitude.
     */
    double getLongitude() const { return this->longitude; }
};

#endif // AED_PROJ2_2021_STOP_H
