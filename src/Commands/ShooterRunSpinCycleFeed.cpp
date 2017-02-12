#include "ShooterRunSpinCycleFeed.h"

ShooterRunSpinCycleFeed::ShooterRunSpinCycleFeed(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ShooterRunSpinCycleFeed::Initialize() {
	//stop
	Robot::shooter->SetSpinCycleFeedSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void ShooterRunSpinCycleFeed::Execute() {
	//go the speed
	Robot::shooter->SetSpinCycleFeedSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterRunSpinCycleFeed::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterRunSpinCycleFeed::End() {
	//stop
	//Robot::shooter->SetSpinCycleFeedSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterRunSpinCycleFeed::Interrupted() {
	End();
}
