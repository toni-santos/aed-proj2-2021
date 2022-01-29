#include <chrono>
#include <iostream>
#include <limits>
#include <string>

#include "../includes/Menu.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
// #include "../includes/filters.h"

void UserInterface::startMenu() {
    unsigned input = getUnsignedInput("(1) Plan\n"
                                      "(0) Exit\n\n",
                                      0, 1);

    switch (input) {
    case 0:
        currentMenu = EXIT;
        break;
    case 1:
        currentMenu = DEPARTURE;
        break;
    }
}

void UserInterface::optionsMenu(
    const std::string &text,
    const std::vector<std::pair<std::string, Menu>> &options) {
    std::cout << CLEAR_SCREEN << text << "\n\n";

    for (int i{1}; i < options.size(); ++i) {
        std::cout << "(" << i << ") " << options.at(i).first << std::endl;
    }

    std::cout << "(0) " << options.front().first << "\n\n";

    unsigned option = getUnsignedInput("Please insert option: ");

    if (option < options.size())
        currentMenu = options.at(option).second;
    else
        errorMessage = "Invalid option!\n";
}

unsigned long UserInterface::getUnsignedInput(std::string prompt,
                                              unsigned long min,
                                              unsigned long max) {
    std::string input;
    unsigned long number;
    bool done = false;

    do {
        input = getStringInput(prompt);

        try {
            number = stoul(input);
            done = true;
        } catch (std::invalid_argument) {
            errorMessage = "Invalid input!\n";
            done = false;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

double UserInterface::getDoubleInput(std::string prompt, double min,
                                     double max) {
    std::string input;
    double number;
    bool done = false;

    do {
        input = getStringInput(prompt);

        try {
            number = stod(input);
            done = true;
        } catch (std::invalid_argument) {
            errorMessage = "Invalid input!\n";
            done = false;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

std::string UserInterface::getStringInput(std::string prompt) {
    std::cout << RED_TEXT << errorMessage << RESET_FORMATTING << prompt;
    errorMessage = "";

    std::string input{};

    std::getline(std::cin, input);
    normalizeInput(input);

    if (std::cin.eof())
        exit();

    return input;
}

void UserInterface::exit() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::cout << "Shutting down..." << std::endl;
}

bool UserInterface::inRange(unsigned long n, unsigned long min,
                            unsigned long max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        errorMessage = "Value outside allowed range!\n";

    return b;
}

bool UserInterface::inRange(double n, double min, double max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        errorMessage = "Value outside allowed range!\n";

    return b;
}

void UserInterface::show(Graph &graph) {
    std::cout << CLEAR_SCREEN << PROGRAM_NAME << '\n' << std::endl;

    switch (currentMenu) {
    case START:
        startMenu();
        break;
    case DEPARTURE:
        departureMenu(graph);
        break;
    case DESTINATION:
        destinationMenu(graph);
        break;
    case WALK:
        walkMenu();
        break;
    case SELECTION:
        selectionMenu();
        break;
    case NIGHT:
        nightMenu();
        break;
    case PLAN:
        planMenu(graph);
        break;
    case EXIT:
        throw Exit();
        break;
    }
}

void UserInterface::departureMenu(Graph &graph) {
    unsigned opt = getUnsignedInput("(1) Coordinates\n"
                                    "(2) Stop\n"
                                    "(0) Go back\n\n"
                                    "Enter departure by: ",
                                    0, 2);

    switch (opt) {
    case 1: {
        double depLatitude =
            getDoubleInput("Insert your latitude value: ", -90., 90.);

        double depLongitude =
            getDoubleInput("Insert your longitude value: ", -180., 180.);

        graph.setStart(depLatitude, depLongitude);
        startCode = "START";
        break;
    }
    case 2:
        startCode = getStringInput("Insert the departure's stop code: ");
        break;
    case 0:
        currentMenu = START;
        return;
    }

    currentMenu = DESTINATION;
}

void UserInterface::destinationMenu(Graph &graph) {
    unsigned opt = getUnsignedInput("(1) Coordinates\n"
                                    "(2) Stop\n"
                                    "(0) Go back\n\n"
                                    "Enter departure by: ",
                                    0, 2);

    switch (opt) {
    case 1: {
        double destLatitude = getDoubleInput(
            "Insert the destination's latitude value: ", -90., 90.);

        double destLongitude = getDoubleInput(
            "Insert the destination's longitude value: ", -180., 180.);

        graph.setEnd(destLatitude, destLongitude);
        endCode = "END";
        break;
    }
    case 2:
        endCode = getStringInput("Insert the destination's stop code: ");
        break;
    case 0:
        currentMenu = START;
        return;
    }

    currentMenu = WALK;
}

void UserInterface::walkMenu() {
    walk = getDoubleInput(
        "Insert a distance you'd be comfortable walking (m): ", 0);

    currentMenu = NIGHT;
}

void UserInterface::nightMenu() {
    std::string opt = getStringInput("Will you be travelling at night (N/y): ");

    if (opt == "Y" || opt == "y")
        night = true;

    currentMenu = SELECTION;
}

void UserInterface::selectionMenu() {
    int opt = getUnsignedInput("(1) Minimize cost\n"
                               "(2) Minimize bus changes\n"
                               "(3) Minimize distance\n"
                               "(4) Minimize stops\n\n"
                               "Choose how you'd like to plan your trip: ",
                               1, 4);

    option = (Option)(opt - 1);

    currentMenu = PLAN;
}

void UserInterface::planMenu(Graph &graph) {
    filter f =
        compositeFilter({walkingFilter(walk), nightFilter(!night, true)});

    switch (option) {
    case MIN_COST:
        // zone changes
        path = graph.dijkstraCostPath(startCode, endCode, f);
        break;

    case MIN_CHANGES:
        // bus changes
        path = graph.dijkstraLinesPath(startCode, endCode, f);
        break;

    case MIN_DISTANCE:
        // normal dijkstra
        path = graph.dijkstraPath(startCode, endCode, f);
        break;

    case MIN_STOPS:
        // stop changes (dfs)
        path = graph.bfsPath(startCode, endCode, f);
        break;
    }

    for (const Node &node : path)
        std::cout << node.stop.getCode() << "\t- " << node.line << "\t- "
                  << node.stop.getName() << std::endl;

    getStringInput("\nPress Enter to continue...\n");

    currentMenu = START;
}
