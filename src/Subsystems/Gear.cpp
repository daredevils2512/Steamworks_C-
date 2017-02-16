#include "Gear.h"
#include "../RobotMap.h"
#include "../Commands/GearIntakeActuate.h"

Gear::Gear() : Subsystem("Gear") {
	limitswitch = RobotMap::gearLimitSwitch;
	solenoid = RobotMap::gearSolenoid;
	previousGearSwitchState = GetLimitSwitch();
}

void Gear::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Gear::GetLimitSwitch() {
	return limitswitch->Get();
}

frc::DoubleSolenoid::Value Gear::GetIntakeDirection() {
	return solenoid->Get();
}

void Gear::ActuateGearIntake(frc::DoubleSolenoid:: Value dir) {
	solenoid->Set(dir);
}

void Gear::UpdateGearActuator() {
	if(GetLimitSwitch() != previousGearSwitchState){
		if(GetIntakeDirection() == frc::DoubleSolenoid::kForward) {
			SetCurrentCommand(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
		}else{
			SetCurrentCommand(new GearIntakeActuate(frc::DoubleSolenoid::kForward));
		}
	}
	previousGearSwitchState = GetLimitSwitch();
}
