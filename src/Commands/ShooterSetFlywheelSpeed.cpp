#include "ShooterSetFlywheelSpeed.h"

ShooterSetFlywheelSpeed::ShooterSetFlywheelSpeed(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ShooterSetFlywheelSpeed::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void ShooterSetFlywheelSpeed::Execute() {
	Robot::shooter->SaveFlywheelSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterSetFlywheelSpeed::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterSetFlywheelSpeed::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterSetFlywheelSpeed::Interrupted() {
	End();
}
