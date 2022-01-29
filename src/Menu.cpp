#include <chrono>
#include <iostream>
#include <limits>
#include <string>

#include "../includes/Menu.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"
// #include "../includes/filters.h"

Menu::Menu() {}

void Menu::startMenu() {

#ifdef TONI
    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);
    night = (now_tm->tm_hour >= 23 || now_tm->tm_hour <= 5);
#else
    night = false;
#endif

    std::string logo = R"(
          /$$$$$$  /$$$$$$$$ /$$$$$$  /$$$$$$$  /$$
         /$$__  $$|__  $$__//$$__  $$| $$__  $$| $$
        | $$  \__/   | $$  | $$  \__/| $$  \ $$| $$  /$$$$$$  /$$$$$$$
        |  $$$$$$    | $$  | $$      | $$$$$$$/| $$ |____  $$| $$__  $$
         \____  $$   | $$  | $$      | $$____/ | $$  /$$$$$$$| $$  \ $$
         /$$  \ $$   | $$  | $$    $$| $$      | $$ /$$__  $$| $$  | $$
        |  $$$$$$/   | $$  |  $$$$$$/| $$      | $$|  $$$$$$$| $$  | $$
         \______/    |__/   \______/ |__/      |__/ \_______/|__/  |__/


                ----------------------------------------------
                |                                            |
                |                (1) Plan                    |
                |                (0) Exit                    |
                |                                            |
                ----------------------------------------------

    )";

    std::cout << CLEAR_SCREEN << logo << std::endl;

    unsigned input = getNumberInput(logo, 0, 1ul);

    switch (input) {
    case 0:
        show(EXIT);
        break;
    case 1:
        show(DEPARTURE);
        break;
    }
}

unsigned long Menu::getNumberInput(std::string prompt, unsigned long min,
                                   unsigned long max) {
    std::string input;
    unsigned long number;
    bool done = false;

    do {
        input = getInput(prompt);

        try {
            number = stoul(input);
            done = true;
        } catch (std::invalid_argument) {
            std::cout << "Invalid input!" << std::endl;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

double Menu::getNumberInput(std::string prompt, double min, double max) {
    std::string input;
    double number;
    bool done = false;

    do {
        input = getInput(prompt);

        try {
            number = stod(input);
            done = true;
        } catch (std::invalid_argument) {
            std::cout << "Invalid input!" << std::endl;
        }
    } while (!done || !inRange(number, min, max));

    return number;
}

std::string Menu::getInput(std::string prompt) {

    std::string input{};

    std::getline(std::cin, input);
    normalizeInput(input);

    if (std::cin.eof())
        exit();

    return input;
}

void Menu::exit() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::cout << "Shutting down..." << std::endl;
}

bool Menu::inRange(unsigned long n, unsigned long min, unsigned long max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        std::cout << "Value outside allowed range!" << std::endl;

    return b;
}

bool Menu::inRange(double n, double min, double max) {
    bool b = (n <= max) && (n >= min);

    if (!b)
        std::cout << "Value outside allowed range!" << std::endl;

    return b;
}

void Menu::show(State state) {
    switch (state) {
    case START:
        startMenu();
        break;
    case DEPARTURE:
        departureMenu();
        break;
    case DESTINATION:
        destinationMenu();
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
        planMenu();
        break;
    case EXIT:
        throw Exit();
        break;
    }
}

void Menu::departureMenu() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::string opts = "Enter departure by:\n\n"
                       "1 - Coordinates\n"
                       "2 - Stop\n"
                       "0 - Return";

    std::cout << opts << std::endl;

    unsigned opt = getNumberInput(opts, 0, 2ul);

    std::string prompt{""};
    int pos{};

    switch (opt) {
    case 1: {
        prompt = "Insert your latitude value: ";
        std::cout << prompt << std::endl;
        double depLatitude = getNumberInput(prompt, -90., 90.);

        prompt = "Insert your longitude value: ";
        std::cout << prompt << std::endl;
        double depLongitude = getNumberInput(opts, -180., 180.);

        graph.setStart(depLatitude, depLongitude);
        startCode = "START";
        break;
        // TODO: calculate stop code here?
    }
    case 2: {
        prompt = "Insert the departure's stop code: ";
        std::cout << prompt;
        this->startCode = getInput(prompt);
        break;
    }
    case 0:
        show(START);
        return;
    }

    show(DESTINATION);
}

void Menu::destinationMenu() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::string opts = "Enter destination by:\n\n"
                       "1 - Coordinates\n"
                       "2 - Stop\n"
                       "0 - Return";

    std::cout << opts << std::endl;

    unsigned opt = getNumberInput(opts, 0, 2ul);

    std::string prompt{""};

    switch (opt) {
    case 1: {
        prompt = "Insert the destination's latitude value: ";
        std::cout << prompt << std::endl;
        double destLatitude = getNumberInput(prompt, -90., 90.);

        prompt = "Insert the destination's longitude value: ";
        std::cout << prompt << std::endl;
        double destLongitude = getNumberInput(opts, -180., 180.);

        graph.setEnd(destLatitude, destLongitude);
        endCode = "END";

        break;
    }
    case 2: {
        prompt = "Insert the destination's stop code: ";
        std::cout << prompt;
        this->endCode = getInput(prompt);
        break;
    }
    case 0:
        show(START);
        return;
    }

    show(WALK);
}

void Menu::walkMenu() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::string prompt = "Insert a distance you'd be comfortable walking (m): ";
    std::cout << prompt << std::flush;

    walk = getNumberInput(prompt);

    show(NIGHT);
}

void Menu::nightMenu() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::string prompt = "Will you be travelling at night (N/y): ";
    std::cout << prompt << std::flush;

    std::string opt = getInput(prompt);

    if (opt == "Y" || opt == "y")
        night = true;

    show(SELECTION);
}

void Menu::selectionMenu() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::string prompt = "Choose how you'd like to plan your trip: \n\n"
                         "1 - Minimize cost\n"
                         "2 - Minimize bus changes\n"
                         "3 - Minimize distance\n"
                         "4 - Minimize stops\n";

    int opt = getNumberInput(prompt, 1, 4ul);

    option = (Option)(opt - 1);

    show(PLAN);
}

void Menu::planMenu() {
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
    // TODO: calculations and all of the algorithms

    for (const Node &node : path)
        std::cout << node.stop.getCode() << "\t- " << node.line << "\t- "
                  << node.stop.getName() << std::endl;

    getInput("");
}
