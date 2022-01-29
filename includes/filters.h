#ifndef AED_PROJ2_2021_FILTERS_H
#define AED_PROJ2_2021_FILTERS_H

#include <functional>
#include <string>
#include <vector>

struct Node;
struct Edge;

/**
 * @brief Filters a connection in a Graph.
 *
 * @param src The source node.
 * @param dest The destination node.
 * @param edge The edge connecting the nodes.
 * @return true if the connection should be accepted.
 * @return false if the connection should be rejected.
 */
using filter =
    std::function<bool(const Node &src, const Node &dest, const Edge &edge)>;

#include "graph.h"

/**
 * @brief Creates a filter that rejects walking edges based on their distance.
 *
 * @param maxWalkDistance The maximum distance allowed.
 * @return A filter with the required constraints.
 */
filter walkingFilter(const double &maxWalkDistance);

/**
 * @brief Creates a filter that accepts or rejects edges based on if their line
 *        is night only.
 *
 * @param day Whether to accept day only lines.
 * @param night Whether to accept night only lines.
 * @return A filter with the required constraints.
 */
filter nightFilter(const bool &day, const bool &night);

/**
 * @brief Creates a filter that rejects lines based on their code.
 *
 * @param lineCode The line code to reject.
 * @return A filter with the required constraints.
 */
filter lineFilter(const std::string &lineCode);

/**
 * @brief Creates a filter that rejects stops based on their code.
 *
 * @param stopCode The stop code to reject.
 * @return A filter with the required constraints.
 */
filter stopFilter(const std::string &stopCode);

/**
 * @brief Creates a filter that follows the constraints of all the filters
 *        given.
 *
 * @param filters The filters to follow.
 * @return A filter with the required constraints.
 */
filter compositeFilter(const std::vector<filter> &filters);

#endif // AED_PROJ2_2021_FILTERS_H
