#ifndef Gear_H
#define Gear_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "PixySubsystem.h"

class Gear : public Subsystem {
private:
	std::shared_ptr<DigitalInput> limitswitch;
	std::shared_ptr<DoubleSolenoid> solenoid;

public:
	//creating the usable functions
	Gear();
	void InitDefaultCommand();

	bool GetLimitSwitch();
	bool GetIntake();
	frc::DoubleSolenoid::Value GetIntakeDirection();
	void ActuateGearIntake(DoubleSolenoid::Value dir);
	void UpdateGearActuator();
private:
	//a bool to save what the previous state of the gear limit switch
	bool previousGearSwitchState;
};

#endif  // Gear_H
