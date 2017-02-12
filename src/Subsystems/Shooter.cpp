#include "Shooter.h"
#include "../RobotMap.h"
#include <cmath>

Shooter::Shooter() : Subsystem("Shooter") {
	//quick defines
	leftFlywheel = RobotMap::shooterLeftFlywheel;
	rightFlywheel = RobotMap::shooterRightFlywheel;
	spinCycleFeed = RobotMap::shooterSpinCycleFeed;
	turretSwivel = RobotMap::shooterTurretSwivel;

	hoodActuator = RobotMap::shooterHoodActuator;

	lastConditionRight = false;
	lastConditionLeft = false;
	maxEncPosition = 4096;
}

//void Shooter::SwivelVisionBased(Nullable< std::vector<int> >  object){ // move me to a command!
//	int pixyWidth = 318;
//	//add "acceptable range"
//	if(object.hasValue()){
//		if(object.GetValue() <3> pixyWidth/2) {
//			// right of center
//		}else if(object[3] != pixyWidth/2){
//			// left of center
//		}else{
//			//centered
//		}
//	}else{
//		// scan
//
//	}
//}

void Shooter::InitDefaultCommand() {

}

//Below are all of the helpful methods of this class :)
void Shooter::ActuateHood(frc::DoubleSolenoid::Value direction){
	//Sets the hood actuator to the passed enum value
	hoodActuator->Set(direction);
}

void Shooter::SetFlywheelSpeed(double speed){
	//Set the flywheels to the appropriate speeds
	leftFlywheel->Set(speed);
	rightFlywheel->Set(-speed);
}

void Shooter::SetSpinCycleFeedSpeed(double speed){
	//Sets the speed of the shooter ball-pusher
	spinCycleFeed->Set(speed);
}

void Shooter::SetSwivelSpeed(double speed){
	//Set the speed to crank the swivel around at
	turretSwivel->Set(speed);
}

bool Shooter::IsHoodActuated() {
	//is it actuated?
	return hoodActuator->Get();
}


int Shooter::GetVirtualDistance(PixySubsystem::ObjectValues object){
	//calculates the distance from the target in inches
	return (0.00349450614331*(pow(object.y,2))) - (0.0873599815179*(object.y)) + 43.068903964768;
}
