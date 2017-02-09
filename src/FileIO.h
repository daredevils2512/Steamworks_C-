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
using namespace std;

class FileIO {
	public:
		static string getFileAsString(string path);
};


#endif /* SRC_FILEIO_H_ */
