//
// Created by toni on 27/01/22.
//

#ifndef AED_PROJ2_2021_MENU_H
#define AED_PROJ2_2021_MENU_H

class UserInterface;

#include "graph.h"

/**
 * @brief Holds the possible menu values.
 */
enum Menu {
    /**
     * @brief Displays an initial menu to start the program.
     */
    START,
    /**
     * @brief Displays a menu to specify the departure (by a stop code or
     * coordinates).
     */
    DEPARTURE,
    /**
     * @brief Displays a menu to specify the destination (by a stop code or
     * coordinates).
     */
    DESTINATION,
    /**
     * @brief Displays a menu to specify by what constraints to optimize the
     * calculated path.
     */
    SELECTION,
    /**
     * @brief Displays a menu to specify a walking distance between stops the
     * user is comfortable with.
     */
    WALK,
    /**
     * @brief Displays a menu to specify if travel is done solely by night.
     */
    NIGHT,
    /**
     * @brief Calculates and displays the path.
     */
    PLAN,
    /**
     * @brief Exits the program.
     */
    EXIT
};

/**
 * @brief Holds the possible ways to calculate a path.
 */
enum Option {
    /**
     * @brief Generates a path passing through the minimum amount of zones.
     */
    MIN_COST,
    /**
     * @brief Generates a path passing through the minimum amount of lines.
     */
    MIN_CHANGES,
    /**
     * @brief Generates a path with the least amount of distance.
     */
    MIN_DISTANCE,
    /**
     * @brief Generates a path passing through the minimum amount of stops.
     */
    MIN_STOPS
};

/**
 * @brief Implements the terminal interface for the user to interact with the
 *        network.
 */
class UserInterface {
    /**
     * @brief Specifies which menu to show.
     */
    Menu currentMenu;

    /**
     * @brief The error message to show.
     */
    std::string errorMessage{};

    /**
     * @brief The code of the initial stop (closest to the given coordinates or
     * given by user input).
     */
    std::string startCode;

    /**
     * @brief The code of the initial stop (closest to the given coordinates or
     * given by user input).
     */
    std::string endCode;

    /**
     * @brief The constraint by which the user wishes to optimize their path.
     */
    Option option;

    /**
     * @brief The distance the user is comfortable walking.
     */
    double walk;

    /**
     * @brief The Nodes that constitute the found path.
     */
    std::list<Node> path{};

    /**
     * @brief Specifies if the user is travelling by night (limiting available
     * lines to nocturnal ones).
     */
    bool night;

    /**
     * @brief Helper method to show a menu with options.
     *
     * @details Each option string will be shown along with its index on the
     *          list. When the user inputs one of the indices of the list
     *          _currentMenu will be set to that option's Menu.
     *
     * @note The first option on the list will be shown last and is
     *       intended to be a way to go back in the navigation tree.
     *
     * @param text Text to show before the options
     * @param options The list of options to show
     */
    void optionsMenu(const std::string &text,
                     const std::vector<std::pair<std::string, Menu>> &options);

    /**
     * @brief Tries to transform a string into an unsigned integer, displaying
     * an error message if it fails.
     *
     * @note There are optional parameters (min and max) to also display an
     * error message if the prompt is outside of the designated limit.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @param prompt Shown to the user.
     * @param min The left bound of the limit (inclusive).
     * @param max The right bound of the limit (inclusive).
     * @return The user input, as an unsigned integer.
     */
    unsigned long getUnsignedInput(std::string prompt, unsigned long min = 0,
                                   unsigned long max = ULONG_MAX);

    /**
     * @brief Tries to transform a string into a double, displaying an error
     *        message if it fails.
     *
     * @note There are optional parameters (min and max) to also display an
     * error message if the prompt is outside of the designated limit.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @param prompt Shown to the user.
     * @param min The left bound of the limit (inclusive).
     * @param max The right bound of the limit (inclusive).
     * @return The user input, as an unsigned integer.
     */
    double getDoubleInput(std::string prompt,
                          double min = std::numeric_limits<double>::min(),
                          double max = std::numeric_limits<double>::max());

    /**
     * @brief Gets a line from stdin and normalizes it.
     *
     * @note Also shows _errorMessage and then resets it.
     *
     * @throws Exit if the EOF bit is set.
     *
     * @param prompt Shown to the user.
     * @return The user input.
     */
    std::string getStringInput(std::string prompt);

    /**
     * @brief Checks if an unsigned integer n is inside the limit [min, max].
     *
     * @param n The number to be checked.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return A boolean that confirms whether or not min <= n <= max.
     */
    bool inRange(unsigned long n, unsigned long min, unsigned long max);

    /**
     * @brief Checks if a double n is inside the limit [min, max].
     *
     * @param n The number to be checked.
     * @param min The left bound of the limit.
     * @param max The right bound of the limit.
     * @return A boolean that confirms whether or not min <= n <= max.
     */
    bool inRange(double n, double min, double max);

    /**
     * @brief Displays an initial menu to start the program.
     */
    void startMenu();

    /**
     * @brief Displays a menu to specify the departure (by a stop code or
     * coordinates).
     */
    void departureMenu(Graph &graph);

    /**
     * @brief Displays a menu to specify the destination (by a stop code or
     * coordinates).
     */
    void destinationMenu(Graph &graph);

    /**
     * @brief Displays a menu to specify a walking distance between stops the
     * user is comfortable with.
     */
    void walkMenu();

    /**
     * @brief Displays a menu to specify if travel is done solely by night.
     */
    void nightMenu();

    /**
     * @brief Displays a menu to specify by what constraints to optimize the
     * calculated path.
     */
    void selectionMenu();

    /**
     * @brief Calculates and displays the path.
     */
    void planMenu(Graph &graph);

public:
    /**
     * @brief Shows the current menu.
     *
     * @param graph The graph.
     */
    void show(Graph &graph);
    /**
     * @brief Shows a message before the program exits.
     */
    void exit();
};

#endif // AED_PROJ2_2021_MENU_H
