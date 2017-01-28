#include "Gear.h"
#include "../RobotMap.h"

Gear::Gear() : Subsystem("Gear") {
	limitswitch = RobotMap::gearLimitSwitch;
	photoeye = RobotMap::gearPhotoeye;
}

void Gear::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

void Gear::GetLimitSwitch() {
	limitswitch->Get();
}

void Gear::GetPhotoeye() {
	photoeye->Get();
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
