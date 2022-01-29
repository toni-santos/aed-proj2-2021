#include "../includes/filters.h"

filter walkingFilter(const double &maxWalkDistance) {
    return [=](const Node &src, const Node &dest, const Edge &edge) -> bool {
        return !(edge.code == "A PE" && edge.distance > maxWalkDistance);
    };
}

filter nightFilter(const bool &day, const bool &night) {
    return [=](const Node &src, const Node &dest, const Edge &edge) -> bool {
        bool isNight = edge.code.back() == 'M';
        return (isNight && night) || (!isNight && day);
    };
}

filter lineFilter(const std::string &lineCode) {
    return [=](const Node &src, const Node &dest, const Edge &edge) -> bool {
        return edge.code != lineCode;
    };
}

filter stopFilter(const std::string &stopCode) {
    return [=](const Node &src, const Node &dest, const Edge &edge) -> bool {
        return dest.stop.getCode() != stopCode;
    };
}

filter compositeFilter(const std::vector<filter> &filters) {
    return [=](const Node &src, const Node &dest, const Edge &edge) -> bool {
        bool c = true;

        for (const filter &f : filters)
            c &= f(src, dest, edge);

        return c;
    };
}
