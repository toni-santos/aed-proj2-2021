#include <vector>
#include <string>
#include <cmath>

#include "../includes/Utils.h"

std::vector<std::string> split(std::string str, char sep) {
	std::string temp;
	std::vector<std::string> final;

	for (auto i : str) {
		if (i == sep) {
			final.push_back(temp);
			temp = "";
		} else {
			temp += i;
		}
	}
	final.push_back(temp);

	return final;
}

double haversine(double lat1, double lon1, double lat2, double lon2) {
	double dLat = (lat2 - lat1) * M_PI / 180.0;
	double dLon = (lon2 - lon1) * M_PI / 180.0;

	lat1 = (lat1) * M_PI / 180.0;
	lat2 = (lat2) * M_PI / 180.0;

	double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
	double c = 2 * asin(sqrt(a));
	return 6371 * c;
}
