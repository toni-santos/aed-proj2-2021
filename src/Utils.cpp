//
// Created by toni on 25/01/22.
//

#include <vector>
#include <string>
#include "../includes/Utils.h"

std::vector<std::string> split(std::string str, char sep) {
	std::string temp;
	std::vector<std::string> final;

	for (auto i : str) {
		if (i == sep) {
			final.push_back(temp);
			temp = "";
		} else {
			temp += i;
		}
	}
	final.push_back(temp);

	return final;
}
