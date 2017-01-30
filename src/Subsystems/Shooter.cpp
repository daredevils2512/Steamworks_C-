#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("ExampleSubsystem") {
	//quick defines
	leftFlywheel = RobotMap::shooterLeftFlywheel;
	rightFlywheel = RobotMap::shooterRightFlywheel;
	spinCycleFeed = RobotMap::shooterSpinCycleFeed;
	turretSwivel = RobotMap::shooterTurretSwivel;

	pixyCamera = RobotMap::shooterPixy;

	leftLimitSwitch = RobotMap::shooterLeftLimitSwitch;
	rightLimitSwitch = RobotMap::shooterRightLimitSwitch;
	hoodActuator = RobotMap::shooterHoodActuator;

}

void Shooter::InitDefaultCommand() {
	//rawr
}

//Below are all of the helpful methods of this class :)
void Shooter::ActuateHood(frc::DoubleSolenoid::Value direction){
	//Sets the hood actuator to the passed enum value
	hoodActuator->Set(direction);
}

void Shooter::SetFlywheelSpeed(double speed){
	//Set the flywheels to the appropriate speeds
	leftFlywheel->Set(speed);
	rightFlywheel->Set(speed);
}

void Shooter::SetSpinCycleFeedSpeed(double speed){
	//Sets the speed of the shooter bottom bit thingy that makes all the stuff go vhoomph
	spinCycleFeed->Set(speed);
}

void Shooter::SetSwivelSpeed(double speed){
	//Set the speed to crank the swivel around at
	turretSwivel->Set(speed);
}

bool Shooter::IsHoodActuated() {
	//is it actuate thx
	return hoodActuator->Get();
}

bool Shooter::IsLeftLimitSwitchPressed(){
	//is pressed?
	return leftLimitSwitch->Get();
}

bool Shooter::IsRightLimitSwitchPressed(){
	// IS PRESS???#??#!!
	return rightLimitSwitch->Get();
}
