#include <iostream>
#include <limits>
#include <string>

#include "../includes/Menu.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"

Menu::Menu() {}

void Menu::startMenu() {
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

    std::cout << logo << std::endl;

    unsigned input = getNumberInput(logo, 0, 1);

    switch (input) {
    case 0:
        show(EXIT);
        break;
    case 1:
        show(DEPARTURE);
        break;
    }
}

unsigned Menu::getNumberInput(std::string prompt, long min, long max) {
    std::string input;
    unsigned number;
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

bool Menu::inRange(long n, long min, long max) {
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

    unsigned opt = getNumberInput(opts, 0, 2);

    std::string prompt{""};
    int pos{};

    switch (opt) {
    case 1:
        prompt = "Insert your latitude value: ";
        std::cout << prompt << std::endl;
        this->depLatitude = getNumberInput(prompt, -90, 90);

        prompt = "Insert your longitude value: ";
        std::cout << prompt << std::endl;
        this->depLongitude = getNumberInput(opts, -180, 180);
        break;
        // TODO: calculate stop code here?
    case 2: {
        prompt = "Insert the departure's stop code: ";
        std::cout << prompt;
        this->startCode = getInput(prompt);
        auto node = graph.getNode(startCode);
        this->depLatitude = node.stop.getLatitude();
        this->depLongitude = node.stop.getLongitude();
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

    unsigned opt = getNumberInput(opts, 0, 2);

    std::string prompt{""};

    switch (opt) {
    case 1:
        prompt = "Insert the destination's latitude value: ";
        std::cout << prompt << std::endl;
        this->destLatitude = getNumberInput(prompt, -90, 90);

        prompt = "Insert the destination's longitude value: ";
        std::cout << prompt << std::endl;
        this->destLongitude = getNumberInput(opts, -180, 180);
        break;
        // TODO: calculate stop code here?
    case 2: {
        prompt = "Insert the destination's stop code: ";
        std::cout << prompt;
        this->endCode = getInput(prompt);
        auto node = graph.getNode(endCode);
        this->destLongitude = node.stop.getLongitude();
        this->destLatitude = node.stop.getLatitude();
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

    walk = getNumberInput(prompt, 0, std::numeric_limits<int>::max());

    show(SELECTION);
}

void Menu::selectionMenu() {
    std::cout << CLEAR_SCREEN << std::flush;
    std::string prompt = "Choose how you'd like to plan your trip: \n\n"
                         "1 - Minimize cost\n"
                         "2 - Minimize bus changes\n"
                         "3 - Minimize cost\n";
    int opt = getNumberInput(prompt, 1, 3);

    switch (opt) {
    case 1:
        this->cost = true;
        break;
    case 2:
        this->changes = true;
        break;
    case 3:
        this->minDistance = true;
        break;
    }

    show(PLAN);
}

void Menu::planMenu() {
    // TODO: calculations and all of the algorithms
}
