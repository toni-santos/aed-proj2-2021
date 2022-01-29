#include <iostream>

#include "../includes/Menu.h"
#include "../includes/Trip.h"
#include "../includes/Utils.h"
#include "../includes/graph.h"

int main() {
    Graph graph{};
    Trip trip{};
    UserInterface ui{};

    std::cout << "Loading..." << std::endl;

    try {
        graph.populate();
    } catch (...) {
        std::cerr << "Error in file!" << std::endl;
        return 1;
    }

    try {
        while (true) {
            ui.show(graph, trip);
        }
    } catch (Exit) {
        ui.exit();
    }

    return 0;
}