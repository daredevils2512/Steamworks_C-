#include "PixySubsystem.h"
#include "../RobotMap.h"

PixySubsystem::PixySubsystem() : Subsystem("ExampleSubsystem") {
	realPixyS = RobotMap::shooterRealPixy;
	fakePixyS = RobotMap::shooterFakePixy;
}

void PixySubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void PixySubsystem::CollectFrameData(std::shared_ptr<frc::SPI> realPixy, std::shared_ptr<frc::SPI> fakePixy) {
	//collects the data from the pixy
	uint8_t receiveArray[2];
	uint8_t fakeReceive[2];
	bool useRealPixy = true;
	bool doneCollecting = false;
	bool saveData = false;
	bool firstTime = false;
	bool foundOneStartValue = false;
	int translatedWord = 0;
	int zeroCount = 0;
	frameData.clear();
	//this loop will keep going until we say we're done collecting data or we've collected 16 zeros
	while(!doneCollecting && zeroCount < 16) {
		if(useRealPixy) {
			realPixy->Read(true, receiveArray, 2);
			translatedWord = (receiveArray[0] << 8) | receiveArray[1];
			//std::cout << translatedWord << std::endl;
			if(saveData) {
				if(FoundZeros(translatedWord)) {
					//if we get a zero back we stop collecting data because it's not an object
					doneCollecting = true;
					saveData = false;
					if(ObjectIsGood(objectData)) {
						frameData.push_back(objectData);
					}
					objectData.clear();
				}else{
					if(IsStartValue(translatedWord)) {
						//if the data returned is the start code then we start collecting the data afterwards
						if(!foundOneStartValue) {
							//checking if we've already found a start value
							foundOneStartValue = true;
							if(!firstTime && ObjectIsGood(objectData)) {
								frameData.push_back(objectData);
							}else{
								firstTime = false;
							}
						}else{
							//otherwise we clear the data for the frame
							frameData.clear();
						}
						//clearing the object data once we're done so we can get the data for the next one
						objectData.clear();
					}else{
						foundOneStartValue = false;
					}
					objectData.push_back(translatedWord);
				}
			}else{
				if(IsStartValue(translatedWord)) {
					//if the data returned is the start value then we know we've hit the end
					//of the current frame so we save the data and start again
					frameData.clear();
					saveData = true;
					firstTime = true;
				}else{
					//otherwise add a zero to our counter
					zeroCount++;
				}
			}
			useRealPixy = false;
		}else{
			//otherwise read data from the fakePixy so we can read from the real one again
			fakePixy->Read(true, fakeReceive, 2);
			useRealPixy = true;
		}
	}
	if(!doneCollecting) {
		emptyFrameCount++;
	}else{
		emptyFrameCount = 0;
	}
}

bool PixySubsystem::ObjectIsGood(Nullable< std::vector<int> > objectVector) {
	//checking to see if the object is what we want by checking the height, width, and x, and y-coords
	return (objectVector.GetValue()[1] - objectVector.GetValue()[2] - objectVector.GetValue()[3] - objectVector.GetValue()[4] - objectVector.GetValue()[5] - objectVector.GetValue()[6]) == 0;
}

bool PixySubsystem::IsStartValue(int value) {
	//checking if the data string returned is equal to the hexadecimal string for starting
	const int startValue = 0xaa55;//43605
	if(value == startValue) {
		return true;
	}else{
		return false;
	}
}

bool PixySubsystem::FoundZeros(int value) {
	//returns true if the pixy sends a zero because that means there's no data found
	if(value == 0) {
		return true;
	}else{
		return false;
	}
}

bool PixySubsystem::IsFrameEmpty() {
	return emptyFrameCount >= 5;
}

std::vector<PixySubsystem::ObjectValues> PixySubsystem::GetObjectData() {
	//getting the object data from the pixy and storing it in an ObjectValues object
	std::vector<ObjectValues> objectAccumulator;
	for(auto object : frameData) {
		ObjectValues currentObject;
		currentObject.checksum = object[1];
		currentObject.signature = object[2];
		currentObject.x = object[3];
		currentObject.y = object[4];
		currentObject.width = object[5];
		currentObject.height = object[6];
		objectAccumulator.push_back(currentObject);
	}
	return objectAccumulator;
}

int PixySubsystem::GetFrameSize() {
	//returns the size of the frame in pixels
	return frameData.size();
}

std::vector<PixySubsystem::ObjectValues> PixySubsystem::GetShooterPixyData() {
	//collecting the data from both the real and fake pixy
	CollectFrameData(realPixyS, fakePixyS);
	return GetObjectData();
}
