//
// Created by toni on 27/01/22.
//

#ifndef AED_PROJ2_2021_MENU_H
#define AED_PROJ2_2021_MENU_H

class Menu;

#include "graph.h"

enum State { START, DEPARTURE, DESTINATION, SELECTION, WALK, PLAN, EXIT };

class Menu {
    Graph graph;
    std::string startCode, endCode;
    double depLatitude, depLongitude, destLatitude, destLongitude;
    unsigned walk;
    bool cost = false, changes = false, minDistance = false;

public:
    Menu();
    Menu(Graph graph) { this->graph = graph; }
    void startMenu();
    unsigned getNumberInput(std::string prompt, long min, long max);
    std::string getInput(std::string prompt);
    void exit();
    bool inRange(long n, long min, long max);
    void show(State state);
    void departureMenu();
    void destinationMenu();
    void walkMenu();
    void selectionMenu();
    void planMenu();
};

#endif // AED_PROJ2_2021_MENU_H
