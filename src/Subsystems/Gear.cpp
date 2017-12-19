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
	//returning the value of the gear limit switch
	if(limitswitch->Get()) {
		return false;
	}else{
		return true;
	}
}

bool Gear::GetIntake() {
	//returns the current state of the solenoid for the gear slot
	if(GetIntakeDirection() == frc::DoubleSolenoid::kReverse) {
		return true;
	}else{
		return false;
	}
}

frc::DoubleSolenoid::Value Gear::GetIntakeDirection() {
	//returns the current state of the solenoid for the gear slot
	return solenoid->Get();
}

void Gear::ActuateGearIntake(frc::DoubleSolenoid:: Value dir) {
	//setting the state the gear solenoid should be
	solenoid->Set(dir);
}

void Gear::UpdateGearActuator() {
	//setting the state the gear solenoid should be
	if(GetLimitSwitch() != previousGearSwitchState){
		if(GetIntakeDirection() == frc::DoubleSolenoid::kForward) {
			SetCurrentCommand(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
		}else{
			SetCurrentCommand(new GearIntakeActuate(frc::DoubleSolenoid::kForward));
		}
	}
	//setting the previous gear switch state to what it is currently so we can compare it later
	previousGearSwitchState = GetLimitSwitch();
}
