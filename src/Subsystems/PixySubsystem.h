#ifndef PixySubsystem_H
#define PixySubsystem_H

#include <Commands/Subsystem.h>
#include "SPI.h"
#include "../Nullable.h"

class PixySubsystem : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<frc::SPI> realPixyS;
	std::shared_ptr<frc::SPI> fakePixyS;
	std::shared_ptr<frc::SPI> realPixyG;
	std::shared_ptr<frc::SPI> fakePixyG;
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

	PixySubsystem();
	void InitDefaultCommand();
	std::vector<PixySubsystem::ObjectValues> GetShooterPixyData();
	std::vector<PixySubsystem::ObjectValues> GetGearPixyData();
	bool IsFrameEmpty();

	int GetFrameSize();

private:
	void CollectFrameData(std::shared_ptr<frc::SPI> realPixy, std::shared_ptr<frc::SPI> fakePixy);
	bool ObjectIsGood(Nullable< std::vector<int> > objectVector);
	std::vector<ObjectValues> GetObjectData();
	bool IsStartValue(int value);
	bool FoundZeros(int value);
};

#endif  // PixySubsystem_H
