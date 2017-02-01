#ifndef Gear_H
#define Gear_H

#include <Commands/Subsystem.h>
#include "WPILib.h"
#include "../Pixy.h"

class Gear : public Subsystem {
private:
	std::shared_ptr<DigitalInput> limitswitch;
	std::shared_ptr<DigitalInput> photoeye;
	std::shared_ptr<DoubleSolenoid> solenoid;

	std::shared_ptr<Pixy> pixyCamera;

	Nullable< Pixy::ObjectValues > targetObject;

public:
	Gear();
	void InitDefaultCommand();
	bool GetLimitSwitch();
	bool GetPhotoeye();
	void ActuateGearIntake(DoubleSolenoid::Value dir);
	void UpdateObjectData();
	bool ObjectExists(Nullable<Pixy::ObjectValues> object);
	Nullable<Pixy::ObjectValues> GetObjectData(int objectIndex);
};

#endif  // Gear_H
