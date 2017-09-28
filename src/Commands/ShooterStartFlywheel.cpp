#include "ShooterStartFlywheel.h"

ShooterStartFlywheel::ShooterStartFlywheel() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShooterStartFlywheel::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ShooterStartFlywheel::Execute() {
	//turns on the flywheel
	Robot::shooter->RunFlywheel();
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterStartFlywheel::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterStartFlywheel::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterStartFlywheel::Interrupted() {
	End();
}
