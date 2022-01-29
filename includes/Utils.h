#ifndef AED_PROJ2_2021_UTILS_H
#define AED_PROJ2_2021_UTILS_H
#include <vector>

/**
 * @brief Exception thrown when the user wants to exit the program.
 */
class Exit {};

/**
 * @brief Splits a string by a character.
 *
 * @param str The string to be split.
 * @param sep The character to use as the separator.
 * @return A vector with all the words in the string that were separated by the
 *         given character.
 */
std::vector<std::string> split(std::string str, char sep);

/**
 * @brief Calculates the distance between two points on a sphere using
 *        Haversine's algorithm.
 *
 * @param lat1 The first point's latitude.
 * @param lon1 The first point's longitude.
 * @param lat2 The second point's latitude.
 * @param lon2 The second point's longitude.
 * @return The distance.
 */
double haversine(double lat1, double lon1, double lat2, double lon2);

/**
 * @brief Normalizes a string.
 *
 * @details Replaces all tabs with spaces, removes duplicate spaces and trims
 *          spaces from the start and the end.
 *
 * @param input The string to normalize.
 */
void normalizeInput(std::string &input);

#endif