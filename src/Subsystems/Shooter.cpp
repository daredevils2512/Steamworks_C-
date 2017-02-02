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

bool Shooter::IsLeftLimitSwitchPressed(){
	//is pressed?
	return leftLimitSwitch->Get();
}

bool Shooter::IsRightLimitSwitchPressed(){
	// is switch pressed?
	return rightLimitSwitch->Get();
}

void Shooter::UpdateObjectData() {
	pixyCamera->CollectFrameData();
}

bool Shooter::ObjectExists(Nullable<Pixy::ObjectValues> object) {
	return (object.HasValue() && !pixyCamera->IsFrameEmpty());
}

Nullable<Pixy::ObjectValues> Shooter::GetObjectData(int objectIndex) {
	targetObject = pixyCamera->GetObjectData(objectIndex);
	if(ObjectExists(targetObject)) {
		return Nullable<Pixy::ObjectValues>(targetObject.GetValue());
	}else{
		return Nullable<Pixy::ObjectValues>();
	}
}
