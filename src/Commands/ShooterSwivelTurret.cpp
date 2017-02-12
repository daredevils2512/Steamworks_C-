#include "ShooterSwivelTurret.h"

ShooterSwivelTurret::ShooterSwivelTurret(double speed) {
	m_speed = speed;
}

// Called just before this Command runs the first time
void ShooterSwivelTurret::Initialize() {
	//stop swivel to prevent weird spinnyness
	//Robot::shooter->SetSwivelSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void ShooterSwivelTurret::Execute() {
	//Set the speed of the swivel when told to
	Robot::shooter->SetSwivelSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterSwivelTurret::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterSwivelTurret::End() {
	//stop
	//Robot::shooter->SetSwivelSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterSwivelTurret::Interrupted() {
	//also stop
	End();
}
