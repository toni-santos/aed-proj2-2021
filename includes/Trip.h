#ifndef AED_PROJ2_2021_TRIP_H
#define AED_PROJ2_2021_TRIP_H

#include "filters.h"

#include <ostream>
#include <set>
#include <string>

/**
 * @brief Holds the possible ways to calculate a path.
 */
enum Strategy {
    /**
     * @brief Generates a path with the least amount of distance.
     */
    MIN_DISTANCE,
    /**
     * @brief Generates a path passing through the minimum amount of zones.
     */
    MIN_COST,
    /**
     * @brief Generates a path passing through the minimum amount of lines.
     */
    MIN_CHANGES,
    /**
     * @brief Generates a path passing through the minimum amount of stops.
     */
    MIN_STOPS
};

class Trip {
    std::string source{""};
    std::string destination{""};
    Strategy strategy{MIN_DISTANCE};
    double maxWalkDistance{0};
    bool day{true};
    bool night{true};
    std::set<std::string> closedLines{};
    std::set<std::string> closedStops{};

public:
    bool hasSource() const;
    bool hasDestination() const;

    std::string getSource() const;
    std::string getDestination() const;
    Strategy getStrategy() const;
    double getMaxWalkDistance() const;
    bool getDay() const;
    bool getNight() const;
    std::set<std::string> getClosedLines() const;
    std::set<std::string> getClosedStops() const;
    filter getFilter() const;

    void setSource(const std::string &source);
    void setDestination(const std::string &destination);
    void setStrategy(const Strategy &strategy);
    void setDay(const bool &day);
    void setNight(const bool &night);
    void setMaxWalkDistance(const double &dist);

    void toggleLine(const std::string &line);
    void toggleStop(const std::string &stop);

    friend std::ostream &operator<<(std::ostream &out, const Trip &trip);
};

#endif