#include "Subsystems/CompressorSubsystem.h"
#include "../RobotMap.h"

CompressorSubsystem::CompressorSubsystem() :
		Subsystem("Compressor")
{
	spike = RobotMap::compressorSpike;
	pressureSwitch = RobotMap::compressorPressureSwitch;
}

void CompressorSubsystem::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void CompressorSubsystem::On() {
	//turns compressor on
	spike->Set(frc::Relay::kForward);
}

void CompressorSubsystem::Off() {
	//turns compressor off
	spike->Set(frc::Relay::kOff);
}

bool CompressorSubsystem::Pressurized() {
	//gets sensor data to check if air tanks are filled or not
	return pressureSwitch->Get();
}
