#include "AutoTimedDriveForward.h"
#include "../Robot.h"

AutoTimedDriveForward::AutoTimedDriveForward(double time) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	SetTimeout(time);
}

// Called just before this Command runs the first time
void AutoTimedDriveForward::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoTimedDriveForward::Execute() {
	//drives forward based off of a time inputed
	Robot::drivetrain->DriveRobotArcade(0.4, 0.0);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoTimedDriveForward::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void AutoTimedDriveForward::End() {
	Robot::drivetrain->DriveRobotArcade(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTimedDriveForward::Interrupted() {
	End();
}
