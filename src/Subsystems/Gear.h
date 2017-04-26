#ifndef Gear_H
#define Gear_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "PixySubsystem.h"

class Gear : public Subsystem {
private:
	std::shared_ptr<DigitalInput> limitswitch;
	std::shared_ptr<DigitalInput> releaseswitch;
	std::shared_ptr<DoubleSolenoid> releasesolenoid;

public:
	Gear();
	void InitDefaultCommand();

	bool GetLimitSwitch();
	bool GetReleaseLimitSwitch();
	frc::DoubleSolenoid::Value GetReleaseDirection();
	void ActuateGearRelease(frc::DoubleSolenoid:: Value dir);
	//void UpdateGearActuator();
private:
	bool previousGearSwitchState;
};

#endif  // Gear_H
