/*
 * FileIO.cpp
 *
 *  Created on: Feb 8, 2017
 *      Author: Loaner
 */

#include "FileIO.h"

#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <ios>
#include <stdlib.h>

std::vector<std::vector<std::string>> FileIO::getLines(std::string path) {
	std::vector<std::vector<std::string>> fileContent;
	std::ifstream ifs(path.c_str());
	while (!ifs.eof()) {
		std::string firstPart;
		std::string lastPart;
		std::getline(ifs, firstPart, ':');
		std::getline(ifs, lastPart);
	}
	ifs.close();
	return fileContent;
}
