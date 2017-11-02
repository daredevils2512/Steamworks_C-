#include "LightToggle.h"
#include "RobotMap.h"

LightToggle::LightToggle() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void LightToggle::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void LightToggle::Execute() {
	std::cout << "On/Off " << RobotMap::spotlightRelay->Get() << std::endl;
	std::cout << "is ALive? " << RobotMap::spotlightRelay->IsAlive() << std::endl;
	if(RobotMap::spotlightRelay->Get() == Relay::kOff){
		RobotMap::spotlightRelay->Set(Relay::kOn);
	}else{
		RobotMap::spotlightRelay->Set(Relay::kOff);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LightToggle::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void LightToggle::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LightToggle::Interrupted() {

}
