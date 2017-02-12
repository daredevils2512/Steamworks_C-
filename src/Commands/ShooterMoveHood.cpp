#include "ShooterMoveHood.h"

ShooterMoveHood::ShooterMoveHood(frc::DoubleSolenoid::Value direction) {
	// Use Requires() here to declare subsystem dependencies
	//Requires(Robot::shooter.get());
	m_direction = direction;
}

// Called just before this Command runs the first time
void ShooterMoveHood::Initialize() {
	//fancy double solenoid off mode
}

// Called repeatedly when this Command is scheduled to run
void ShooterMoveHood::Execute() {
	//set solenoid to do what we want it to do
	Robot::shooter->ActuateHood(m_direction);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterMoveHood::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterMoveHood::End() {
	//reset to off
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterMoveHood::Interrupted() {
	End();
}
