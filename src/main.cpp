#include <iostream>
#include "../includes/Reader.h"

int main() {
	Reader reader;

	reader.readStops();
	reader.readLines();
	reader.print();

	return 0;
}
