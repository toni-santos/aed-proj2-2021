#ifndef AED_PROJ2_2021_UTILS_H
#define AED_PROJ2_2021_UTILS_H
#include <vector>

class Exit {};

std::vector<std::string> split(std::string str, char sep);
double haversine(double lat1, double lon1, double lat2, double lon2);
void normalizeInput(std::string &input);

#endif