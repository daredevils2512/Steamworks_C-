#include "ShooterManualRunFlywheel.h"
#include "../Robot.h"

ShooterManualRunFlywheel::ShooterManualRunFlywheel() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShooterManualRunFlywheel::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterManualRunFlywheel::Execute() {
	Robot::shooter->SetFlywheelSpeed(Robot::oi->GetTranslatedThrottle());
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterManualRunFlywheel::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterManualRunFlywheel::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterManualRunFlywheel::Interrupted() {

}
