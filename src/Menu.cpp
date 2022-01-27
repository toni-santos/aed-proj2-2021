#include <string>
#include <iostream>
#include <limits>

#include "../includes/Menu.h"
#include "../includes/Utils.h"
#include "../includes/constants.h"

Menu::Menu() {
}

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
				|                (1) Plan		             |
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
		case COST:
			costMenu();
			break;
		case BUS_CHANGES:
			changesMenu();
			break;
		case DISTANCE:
			distanceMenu();
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

	std::string prompt {""};
	int pos {};

	switch (opt) {
		case 1:
			prompt = "Insert your latitude value: ";
			std::cout << prompt << std::endl;
			this->depLatitude = getNumberInput(prompt , -90, 90);

			prompt = "Insert your longitude value: ";
			std::cout << prompt << std::endl;
			this->depLongitude = getNumberInput(opts, -180, 180);
			break;
			// TODO: calculate stop code here?
		case 2:
			prompt = "Insert the departure's stop code: ";
			std::cout << prompt;
			this->startCode = getInput(prompt);
			pos = graph.findNodeIdx(startCode);
			this->depLatitude = graph.getNodes().at(pos).stop.getLatitude();
			this->depLongitude = graph.getNodes().at(pos).stop.getLongitude();
			break;
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

	std::string prompt {""};
	int pos {};

	switch (opt) {
		case 1:
			prompt = "Insert the destination's latitude value: ";
			std::cout << prompt << std::endl;
			this->destLatitude = getNumberInput(prompt , -90, 90);

			prompt = "Insert the destination's longitude value: ";
			std::cout << prompt << std::endl;
			this->destLongitude = getNumberInput(opts, -180, 180);
			break;
			// TODO: calculate stop code here?
		case 2:
			prompt = "Insert the destination's stop code: ";
			std::cout << prompt;
			this->endCode = getInput(prompt);
			pos = graph.findNodeIdx(endCode);
			this->destLongitude = graph.getNodes().at(pos).stop.getLongitude();
			this->destLatitude = graph.getNodes().at(pos).stop.getLatitude();
			break;
		case 0:
			show(START);
			return;
	}

	show(WALK);
}

void Menu::walkMenu() {
	std::cout << CLEAR_SCREEN << std::flush;
	std::string prompt = "Insert a distance you'd be comfortable walking (default: 50(m)): ";
	std::cout << prompt << std::flush;

	walk = getNumberInput(prompt, 0, std::numeric_limits<int>::max());

	show(COST);
}

void Menu::costMenu() {
	std::cout << CLEAR_SCREEN << std::flush;
	std::string prompt = "Would you like to minimize costs (N/y)? ";
	std::cout << prompt << std::flush;

	std::string opt = getInput(prompt);

	if (opt == "Y" || opt == "y") {
		this->cost = true;
	}

	show(BUS_CHANGES);
}

void Menu::changesMenu() {
	std::cout << CLEAR_SCREEN << std::flush;
	std::string prompt = "Would you like to minimize bus changes (N/y)? ";
	std::cout << prompt << std::flush;

	std::string opt = getInput(prompt);

	if (opt == "Y" || opt == "y") {
		this->changes = true;
	}

	show(DISTANCE);
}

void Menu::distanceMenu() {
	std::cout << CLEAR_SCREEN << std::flush;
	std::string prompt = "Would you like to minimize the overall distance (N/y)? ";
	std::cout << prompt << std::flush;

	std::string opt = getInput(prompt);

	if (opt == "Y" || opt == "y") {
		this->minDistance = true;
	}

	show(PLAN);
}

void Menu::planMenu() {
	// TODO: calculations and all of the algorithms
}
