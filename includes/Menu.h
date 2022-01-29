//
// Created by toni on 27/01/22.
//

#ifndef AED_PROJ2_2021_MENU_H
#define AED_PROJ2_2021_MENU_H

class Menu;

#include "graph.h"

enum State {
    START,
    DEPARTURE,
    DESTINATION,
    SELECTION,
    WALK,
    NIGHT,
    PLAN,
    EXIT
};

enum Option { MIN_COST, MIN_CHANGES, MIN_DISTANCE, MIN_STOPS };

class Menu {
    Graph graph;
    std::string startCode, endCode;
    Option option;
    unsigned walk;
    std::list<Node> path{};
    bool night;

    unsigned long getNumberInput(std::string prompt, unsigned long min = 0,
                                 unsigned long max = ULONG_MAX);
    double getNumberInput(std::string prompt, double min, double max);
    std::string getInput(std::string prompt);
    bool inRange(unsigned long n, unsigned long min, unsigned long max);
    bool inRange(double n, double min, double max);

public:
    Menu();
    Menu(Graph graph) { this->graph = graph; }
    void startMenu();
    void exit();
    void show(State state);
    void departureMenu();
    void destinationMenu();
    void walkMenu();
    void selectionMenu();
    void planMenu();
    void nightMenu();
};

#endif // AED_PROJ2_2021_MENU_H
