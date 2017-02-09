/*
 * FileIO.cpp
 *
 *  Created on: Feb 8, 2017
 *      Author: Loaner
 */

#include <FileIO.h>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

using namespace std;

string FileIO::getFileAsString(string path){
	std::ifstream ifs("/" + path);
	std::string content( (std::istreambuf_iterator<char>(ifs) ),
					   (std::istreambuf_iterator<char>()    ) );
	return content;
}
