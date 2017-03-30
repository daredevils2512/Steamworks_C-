#include "Shooter.h"
#include "../RobotMap.h"
#include <cmath>

Shooter::Shooter() : Subsystem("Shooter") {
	//quick defines
	flywheel = RobotMap::shooterFlywheel;
	spinCycleFeed = RobotMap::shooterSpinCycleFeed;
	turretSwivel = RobotMap::shooterTurretSwivel;
	bottomBooster = RobotMap::shooterBottomBooster;
	topBooster = RobotMap::shooterTopBooster;

	hoodActuator = RobotMap::shooterHoodActuator;

	lastConditionRight = false;
	lastConditionLeft = false;
	maxEncPosition = 5000;//4500
	shooterSpeed = 2250;
}

void Shooter::InitDefaultCommand() {

}

//Below are all of the helpful methods of this class :)
void Shooter::ActuateHood(frc::DoubleSolenoid::Value direction){
	//Sets the hood actuator to the passed enum value
	hoodActuator->Set(direction);
}

void Shooter::SetFlywheelSpeed(double speed){
	//Set the flywheels to the appropriate speeds
	if((speed <= 1) && (speed >=-1)) {
		flywheel->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	}else{
		flywheel->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
	}
	flywheel->Set(speed);
}

void Shooter::SetBoosterSpeed(double speed) {
	bottomBooster->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	bottomBooster->Set(speed);
	topBooster->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	topBooster->Set(speed);
}

void Shooter::SetSpinCycleFeedSpeed(double speed){
	//Sets the speed of the shooter ball-pusher
	spinCycleFeed->Set(speed);
}

void Shooter::SetSwivelSpeed(double speed){
	//Set the speed to crank the swivel around at
	turretSwivel->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
	turretSwivel->Set(speed);
}

double Shooter::GetSwivelPosition() {
	return turretSwivel->GetEncPosition();
}

bool Shooter::IsHoodActuated() {
	//is it actuated?
	return hoodActuator->Get();
}


double Shooter::GetVirtualDistance(PixySubsystem::ObjectValues object){
	//calculates the distance from the target in inches
	return (0.00349450614331*(pow(object.y,2))) - (0.0873599815179*(object.y)) + 43.068903964768;
}

void Shooter::SaveShooterSpeed(double speed) {
	shooterSpeed = speed;
}

double Shooter::GetShooterSpeed() {
	return shooterSpeed;
}
