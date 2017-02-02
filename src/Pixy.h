/*
 * Pixy.h
 *
 *  Created on: Jan 20, 2017
 *      Author: troym
 */

#ifndef PIXY_H_
#define PIXY_H_

#include <iostream>
#include <vector>
#include "Nullable.h"
#include "WPILib.h"


//a.k.a. the classy class
class Pixy {

private:
	std::shared_ptr<frc::SPI> m_realPixy;
	std::shared_ptr<frc::SPI> m_fakePixy;
	std::vector< std::vector<int> > frameData;
	std::vector<int> objectData;
	int emptyFrameCount = 0;

public:

	struct ObjectValues {
		int checksum;
		int signature;
		int x;
		int y;
		int width;
		int height;
	};

	Pixy(std::shared_ptr<frc::SPI> realPixy, std::shared_ptr<frc::SPI> fakePixy);

	//adjusts settings of each pixy camera to the specifications required for communication
	void Setup(std::shared_ptr<frc::SPI> pixy);
	//collects data starting from the first "start value" (43605 or aa55) and ending when two
	//zeros are detected - signaling there is no more data
	void CollectFrameData();
	//performs multiple tests on object in question to determine if the data is good, only
	//returns good if object data passes all tests, otherwise it will print an error
	bool ObjectIsGood(Nullable< std::vector<int> > objectVector);
	//checks if argument is equal to the start value of 43605 in decimal or aa55 in hexadecimal
	bool IsStartValue(int value);
	//checks if argument is equal to zero - only possible if both of the bytes used to calculate
	//the argument were zero
	bool FoundZeros(int value);
	//returns requested value of specified object or sets HasValue() to false if object data is not good

	bool IsFrameEmpty();

	Nullable< ObjectValues > GetObjectData(int objectIndex);

	int GetFrameSize();

};


#endif /* PIXY_H_ */
