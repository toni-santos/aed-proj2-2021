#define _USE_MATH_DEFINES

#include <cmath>
#include <string>

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

    lat1 = (lat1)*M_PI / 180.0;
    lat2 = (lat2)*M_PI / 180.0;

    double a =
        pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * asin(sqrt(a));
    return 6371 * c;
}

void normalizeInput(std::string &input) {
    char last = 0;
    size_t i = 0;
    while (i < input.length()) {
        char &c = input.at(i);

        // Replace tabs with spaces
        if (c == '\t')
            c = ' ';

        // Delete character if it is a space at the begining, at the end or
        // after another space
        if (c == ' ' &&
            (last == ' ' || last == 0 || i == input.length() - 1 || i == 0)) {
            input.erase(i, 1);

            // If we're outside the string, go back one
            if (i == input.length())
                i--;
        } else {
            i++;
            last = c;
        }
    }
}