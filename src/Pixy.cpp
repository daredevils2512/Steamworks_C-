#include "Pixy.h"

Pixy::Pixy(std::shared_ptr<frc::SPI> realPixy, std::shared_ptr<frc::SPI> fakePixy) {
	m_realPixy = realPixy;
	m_fakePixy = fakePixy;
	Setup(m_realPixy);
	Setup(m_fakePixy);
}

void Pixy::Setup(std::shared_ptr<frc::SPI> pixy) {
	//Most Significant Byte is sent first, data on rising edge, clock is active high,
	//chip is active low, set clock to 1000000 hz
	pixy->SetMSBFirst();
	pixy->SetSampleDataOnRising();
	pixy->SetClockActiveHigh();
	pixy->SetChipSelectActiveLow();
	pixy->SetClockRate(1000000.0);
}

void Pixy::CollectFrameData() {
	uint8_t receiveArray[2];
	uint8_t fakeReceive[2];
	bool useRealPixy = true;
	bool doneCollecting = false;
	bool saveData = false;
	bool firstTime = false;
	bool foundOneStartValue = false;
	int translatedWord = 0;
	int zeroCount = 0;
	while(!doneCollecting && zeroCount < 16) {
		if(useRealPixy) {
			m_realPixy->Read(true, receiveArray, 2);
			translatedWord = (receiveArray[0] << 8) | receiveArray[1];
			if(saveData) {
				if(FoundZeros(translatedWord)) {
					doneCollecting = true;
					saveData = false;
					if(ObjectIsGood(objectData)) {
						frameData.push_back(objectData);
					}
					objectData.clear();
				}else{
					if(IsStartValue(translatedWord)) {
						if(!foundOneStartValue) {
							foundOneStartValue = true;
							if(!firstTime && ObjectIsGood(objectData)) {
								frameData.push_back(objectData);
							}else{
								firstTime = false;
							}
						}else{
							frameData.clear();
						}
						objectData.clear();
					}else{
						foundOneStartValue = false;
					}
					objectData.push_back(translatedWord);
				}
			}else{
				if(IsStartValue(translatedWord)) {
					frameData.clear();
					saveData = true;
					firstTime = true;
				}else{
					zeroCount++;
				}
			}
			useRealPixy = false;
		}else{
			m_fakePixy->Read(true, fakeReceive, 2);
			useRealPixy = true;
		}
	}
	if(!doneCollecting) {
		emptyFrameCount++;
	}else{
		emptyFrameCount = 0;
	}
}

bool Pixy::ObjectIsGood(std::vector<int> objectVector) {
	return (objectVector[1] - objectVector[2] - objectVector[3] - objectVector[4] - objectVector[5] - objectVector[6]) == 0;
}

bool Pixy::IsStartValue(int value) {
	const int startValue = 0xaa55;//43605
	if(value == startValue) {
		return true;
	}else{
		return false;
	}
}

bool Pixy::FoundZeros(int value) {
	if(value == 0) {
		return true;
	}else{
		return false;
	}
}

bool Pixy::IsFrameEmpty() {
	return emptyFrameCount >= 5;
}

Nullable< std::vector<int> > Pixy::GetObjectData(int objectIndex) {
	/*
	 * 0 = AA55
	 * 1 = Checksum
	 * 2 = id
	 * 3 = x
	 * 4 = y
	 * 5 = width
	 * 6 = height
	 */
	if((signed)frameData.size() > objectIndex) {
		return Nullable< std::vector<int> >(frameData[objectIndex]);
	}
	return Nullable< std::vector<int> >();
}
