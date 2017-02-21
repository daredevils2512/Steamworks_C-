/*
 * FileIO.h
 *
 *  Created on: Feb 8, 2017
 *      Author: Loaner
 */

#ifndef SRC_FILEIO_H_
#define SRC_FILEIO_H_
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

class FileIO {
	public:
		static std::string getFileAsString(std::string path);
		std::vector<std::vector<std::string>> getLines(std::string path);
};


#endif /* SRC_FILEIO_H_ */
