#ifndef Gear_H
#define Gear_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
class Gear : public Subsystem {
private:
	std::shared_ptr<DigitalInput> limitswitch;
	std::shared_ptr<DigitalInput> photoeye;
	std::shared_ptr<DoubleSolenoid> solenoid;

public:
	Gear();
	void InitDefaultCommand();
	void GetLimitSwitch();
	void GetPhotoeye();
	void ActuateGearIntake(DoubleSolenoid::Value dir);
};

#endif  // Gear_H
