#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("ExampleSubsystem") {
	//quick defines
	LeftFlywheel = RobotMap::shooterLeftFlywheel;
	RightFlywheel = RobotMap::shooterRightFlywheel;
	SpinCycleFeed = RobotMap::shooterSpinCycleFeed;
	TurretSwivel = RobotMap::shooterTurretSwivel;

	LeftLimitSwitch = RobotMap::shooterLeftLimitSwitch;
	RightLimitSwitch = RobotMap::shooterRightLimitSwitch;
	HoodActuator = RobotMap::shooterHoodActuator;

}

void Shooter::InitDefaultCommand() {
	//rawr
}

//Below are all of the helpful methods of this class :)
void Shooter::ActuateHood(frc::DoubleSolenoid::Value direction){
	//Sets the hood actuator to the passed enum value
	HoodActuator->Set(direction);
}

void Shooter::SetFlywheelSpeed(double speed){
	//Set the flywheels to the appropriate speeds
	LeftFlywheel->Set(speed);
	RightFlywheel->Set(speed);
}

void Shooter::SetSpinCycleFeedSpeed(double speed){
	//Sets the speed of the shooter bottom bit thingy that makes all the stuff go vhoomph
	SpinCycleFeed->Set(speed);
}

void Shooter::SetSwivelSpeed(double speed){
	//Set the speed to crank the swivel around at
	TurretSwivel->Set(speed);
}

bool Shooter::IsHoodActuated() {
	//is it actuate thx
	return HoodActuator->Get();
}

bool Shooter::IsLeftLimitSwitchPressed(){
	//is pressed?
	return LeftLimitSwitch->Get();
}

bool Shooter::IsRightLimitSwitchPressed(){
	// IS PRESS???#??#!!
	return RightLimitSwitch->Get();
}
