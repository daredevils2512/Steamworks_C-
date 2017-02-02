#include "AutoDrive.h"

AutoDrive::AutoDrive(double radius, double outerSpeed, Drivetrain::Direction direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_radius = radius;
	m_outerSpeed = outerSpeed;
	m_direction = direction;
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
	Robot::drivetrain->AutoSetSpeeds(Robot::drivetrain->AutoCalcSpeeds(m_radius, m_outerSpeed, m_direction));
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void AutoDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {

}
