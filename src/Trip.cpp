#include "../includes/Trip.h"

bool Trip::hasSource() const { return source != ""; }

bool Trip::hasDestination() const { return destination != ""; }

std::string Trip::getSource() const { return source; }

std::string Trip::getDestination() const { return destination; }

Strategy Trip::getStrategy() const { return strategy; }

double Trip::getMaxWalkDistance() const { return maxWalkDistance; }

bool Trip::getDay() const { return day; }

bool Trip::getNight() const { return night; }

std::set<std::string> Trip::getClosedLines() const { return closedLines; }

std::set<std::string> Trip::getClosedStops() const { return closedStops; }

filter Trip::getFilter() const {
    std::vector<filter> filters{};

    filters.push_back(nightFilter(day, night));
    filters.push_back(walkingFilter(maxWalkDistance));

    for (const std::string &line : closedLines)
        filters.push_back(lineFilter(line));
    for (const std::string &stop : closedStops)
        filters.push_back(stopFilter(stop));

    return compositeFilter(filters);
}

void Trip::setSource(const std::string &src) { source = src; }

void Trip::setDestination(const std::string &dest) { destination = dest; }

void Trip::setStrategy(const Strategy &strat) { strategy = strat; }

void Trip::setDay(const bool &day) { this->day = day; }

void Trip::setNight(const bool &night) { this->night = night; }

void Trip::setMaxWalkDistance(const double &dist) { maxWalkDistance = dist; }

void Trip::toggleLine(const std::string &line) {
    auto i = closedLines.find(line);
    if (i != closedLines.end())
        closedLines.erase(i);
    else
        closedLines.insert(line);
}

void Trip::toggleStop(const std::string &stop) {
    auto i = closedStops.find(stop);
    if (i != closedStops.end())
        closedStops.erase(i);
    else
        closedStops.insert(stop);
}

std::ostream &operator<<(std::ostream &out, const Trip &trip) {
    if (trip.hasSource())
        out << "Starting stop: " << trip.getSource() << '\n';
    else
        out << "Starting stop not specified\n";

    if (trip.hasDestination())
        out << "Destination stop: " << trip.getDestination() << '\n';
    else
        out << "Destination stop not specified\n";

    switch (trip.getStrategy()) {
    case MIN_CHANGES:
        out << "Minimizing line changes\n";
        break;
    case MIN_COST:
        out << "Minimizing cost\n";
        break;
    case MIN_DISTANCE:
        out << "Minimizing distance\n";
        break;
    case MIN_STOPS:
        out << "Minimizing stops\n";
        break;
    }

    if (trip.maxWalkDistance)
        out << "You are willing to walk " << trip.maxWalkDistance << "m\n";

    if (trip.closedLines.size())
        out << trip.closedLines.size() << " lines have been closed\n";
    else
        out << "No lines have been closed\n";

    if (trip.closedStops.size())
        out << trip.closedStops.size() << " stops have been closed\n";
    else
        out << "No stops have been closed\n";

    if (!trip.day)
        out << "Avoiding day only lines\n";
    if (!trip.night)
        out << "Avoiding night only lines\n";

    return out;
}