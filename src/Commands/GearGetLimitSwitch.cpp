#include "GearGetLimitSwitch.h"
#include "../Subsystems/Gear.h"
#include "../Robot.h"

GearGetLimitSwitch::GearGetLimitSwitch() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::gear.get());
}

// Called just before this Command runs the first time
void GearGetLimitSwitch::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearGetLimitSwitch::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool GearGetLimitSwitch::IsFinished() {
	//inverted so it finishes when the switch is released
	return !Robot::gear->GetLimitSwitch();
}

// Called once after isFinished returns true
void GearGetLimitSwitch::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearGetLimitSwitch::Interrupted() {

}
