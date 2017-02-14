#include "ShooterPOVHoodControl.h"
#include "../Robot.h"

ShooterPOVHoodControl::ShooterPOVHoodControl() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShooterPOVHoodControl::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterPOVHoodControl::Execute() {
	Robot::shooter->ActuateHood(Robot::oi->POVHoodControl());
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterPOVHoodControl::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterPOVHoodControl::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterPOVHoodControl::Interrupted() {

}
