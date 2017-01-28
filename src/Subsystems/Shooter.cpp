#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("ExampleSubsystem") {
	LeftFlywheel = RobotMap::shooterLeftFlywheel;
	RightFlywheel = RobotMap::shooterRightFlywheel;
	SpinCycleFeed = RobotMap::shooterSpinCycleFeed;
	TurretSwivel = RobotMap::shooterTurretSwivel;

	LeftLimitSwitch = RobotMap::shooterLeftLimitSwitch;
	RightLimitSwitch = RobotMap::shooterRightLimitSwitch;
	HoodActuator = RobotMap::shooterHoodActuator;

}

void Shooter::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Shooter::ActuateHood(frc::DoubleSolenoid::Value direction){
	HoodActuator->Set(direction);
}

void Shooter::SetFlywheelSpeed(double speed){
	LeftFlywheel->Set(speed);
	RightFlywheel->Set(speed);
}

void Shooter::SetSpinCycleFeedSpeed(double speed){
	SpinCycleFeed->Set(speed);
}

void Shooter::SetSwivelSpeed(double speed){
	TurretSwivel->Set(speed);
}

bool Shooter::IsHoodActuated() {
	return HoodActuator->Get();
}

bool Shooter::IsLeftLimitSwitchPressed(){
	return LeftLimitSwitch->Get();
}

bool Shooter::IsRightLimitSwitchPressed(){
	return RightLimitSwitch->Get();
}
