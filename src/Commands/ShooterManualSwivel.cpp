#include "ShooterManualSwivel.h"
#include "../Subsystems/Shooter.h"
#include "../Robot.h"

ShooterManualSwivel::ShooterManualSwivel() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShooterManualSwivel::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterManualSwivel::Execute() {
	Robot::shooter->SetSwivelSpeed(Robot::oi->GetManualShooterSwivel());
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterManualSwivel::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterManualSwivel::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterManualSwivel::Interrupted() {
	Robot::shooter->SetSwivelSpeed(0.0);
}
