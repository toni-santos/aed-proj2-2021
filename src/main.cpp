#include <iostream>
#include "../includes/graph.h"
#include "../includes/Menu.h"
#include "../includes/Utils.h"

int main() {
	Graph graph(2487, true);

	try {
		graph.populate();
	} catch (...) {
		std::cerr << "Error in file!" << std::endl;
		return 1;
	}

	Menu menu = Menu(graph);

	try {
		while (true) {
			menu.show(START);
		}
	} catch (Exit) {
		menu.exit();
	}

	return 0;
}
