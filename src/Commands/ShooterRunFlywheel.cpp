#include "ShooterRunFlywheel.h"

ShooterRunFlywheel::ShooterRunFlywheel(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ShooterRunFlywheel::Initialize() {
	Robot::shooter->SetFlywheelSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void ShooterRunFlywheel::Execute() {
	Robot::shooter->SetFlywheelSpeed(m_speed);
	Robot::shooter->RunFlywheel();
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterRunFlywheel::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ShooterRunFlywheel::End() {
	//Robot::shooter->SetFlywheelSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterRunFlywheel::Interrupted() {
	End();
}
