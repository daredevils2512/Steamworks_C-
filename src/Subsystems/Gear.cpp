#include "Gear.h"
#include "../RobotMap.h"

Gear::Gear() : Subsystem("Gear") {
	limitswitch = RobotMap::gearLimitSwitch;
	releaseswitch = RobotMap::gearReleaseLimitSwitch;
	releasesolenoid = RobotMap::gearActiveRelease;
	previousGearSwitchState = GetLimitSwitch();

}

void Gear::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

bool Gear::GetLimitSwitch() {
	return !limitswitch->Get();
}
bool Gear::GetReleaseLimitSwitch() {
	return !releaseswitch->Get();
}

frc::DoubleSolenoid::Value Gear::GetIntakeDirection() {
	return solenoid->Get();
}

frc::DoubleSolenoid::Value Gear::GetReleaseDirection() {
	return releasesolenoid->Get();
}

void Gear::ActuateGearIntake(frc::DoubleSolenoid:: Value dir) {
	solenoid->Set(dir);
}

void Gear::ActuateGearRelease(frc::DoubleSolenoid:: Value dir) {
	releasesolenoid->Set(dir);
}

//void Gear::UpdateGearActuator() {
//	if(GetLimitSwitch() != previousGearSwitchState){
//		if(GetIntakeDirection() == frc::DoubleSolenoid::kForward) {
//			SetCurrentCommand(new GearIntakeActuate(frc::DoubleSolenoid::kReverse));
//		}else{
//			SetCurrentCommand(new GearIntakeActuate(frc::DoubleSolenoid::kForward));
//		}
//	}
//	previousGearSwitchState = GetLimitSwitch();
//}
