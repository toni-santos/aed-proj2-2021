#include "../includes/Menu.h"
#include "../includes/Utils.h"
#include "../includes/graph.h"
#include <iostream>

int main() {
    Graph graph{};
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
            ui.show(graph);
        }
    } catch (Exit) {
        ui.exit();
    }

    return 0;
}