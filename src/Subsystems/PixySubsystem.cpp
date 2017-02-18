#include "PixySubsystem.h"
#include "../RobotMap.h"

PixySubsystem::PixySubsystem() : Subsystem("ExampleSubsystem") {
	realPixyS = RobotMap::shooterRealPixy;
	fakePixyS = RobotMap::shooterFakePixy;
	realPixyG = RobotMap::gearRealPixy;
	fakePixyG = RobotMap::gearFakePixy;
}

void PixySubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void PixySubsystem::CollectFrameData(std::shared_ptr<frc::SPI> realPixy, std::shared_ptr<frc::SPI> fakePixy) {
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
	while(!doneCollecting && zeroCount < 16) {
		if(useRealPixy) {
			realPixy->Read(true, receiveArray, 2);
			translatedWord = (receiveArray[0] << 8) | receiveArray[1];
			std::cout << "word: " << translatedWord << " " << std::hex << translatedWord << std::dec << std::endl;
			if(saveData) {
				if(FoundZeros(translatedWord)) {
					std::cout << "found zeros" << std::endl;
					doneCollecting = true;
					saveData = false;
					if(ObjectIsGood(objectData)) {
						std::cout << "add object" << std::endl;
						frameData.push_back(objectData);
					}
					objectData.clear();
				}else{
					if(IsStartValue(translatedWord)) {
						if(!foundOneStartValue) {
							foundOneStartValue = true;
							if(!firstTime && ObjectIsGood(objectData)) {
								std::cout << "add object (2)" << std::endl;
								frameData.push_back(objectData);
							}else{
								firstTime = false;
							}
						}else{
							std::cout << "clear frame" << std::endl;
							frameData.clear();
						}
						objectData.clear();
					}else{
						foundOneStartValue = false;
					}
					std::cout << "add word" << std::endl;
					objectData.push_back(translatedWord);
				}
			}else{
				if(IsStartValue(translatedWord)) {
					std::cout << "clear frame (2)" << std::endl;
					frameData.clear();
					saveData = true;
					firstTime = true;
				}else{
					zeroCount++;
				}
			}
			useRealPixy = false;
		}else{
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
	return (objectVector.GetValue()[1] - objectVector.GetValue()[2] - objectVector.GetValue()[3] - objectVector.GetValue()[4] - objectVector.GetValue()[5] - objectVector.GetValue()[6]) == 0;
}

bool PixySubsystem::IsStartValue(int value) {
	const int startValue = 0xaa55;//43605
	if(value == startValue) {
		return true;
	}else{
		return false;
	}
}

bool PixySubsystem::FoundZeros(int value) {
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
	std::vector<ObjectValues> objectAccumulator;
	std::cout << "frameData size" << frameData.size() << std::endl;
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
	return frameData.size();
}

std::vector<PixySubsystem::ObjectValues> PixySubsystem::GetShooterPixyData() {
	CollectFrameData(realPixyS, fakePixyS);
	return GetObjectData();
}

std::vector<PixySubsystem::ObjectValues> PixySubsystem::GetGearPixyData() {
	CollectFrameData(realPixyG, fakePixyG);
	return GetObjectData();
}


