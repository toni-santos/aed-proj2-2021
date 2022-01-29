#ifndef AED_PROJ2_2021_FILTERS_H
#define AED_PROJ2_2021_FILTERS_H

#include <functional>
#include <string>
#include <vector>

struct Node;
struct Edge;

using filter =
    std::function<bool(const Node &src, const Node &dest, const Edge &edge)>;

#include "graph.h"

filter walkingFilter(const double &maxWalkDistance);
filter nightFilter(const bool &day, const bool &night);
filter lineFilter(const std::string &lineCode);
filter stopFilter(const std::string &stopCode);
filter compositeFilter(const std::vector<filter> &filters);

#endif // AED_PROJ2_2021_FILTERS_H
