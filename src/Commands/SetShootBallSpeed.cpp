#include "SetShootBallSpeed.h"
#include "../Robot.h"

SetShootBallSpeed::SetShootBallSpeed(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void SetShootBallSpeed::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SetShootBallSpeed::Execute() {
	Robot::shooter->SaveShooterSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShootBallSpeed::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SetShootBallSpeed::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShootBallSpeed::Interrupted() {

}
