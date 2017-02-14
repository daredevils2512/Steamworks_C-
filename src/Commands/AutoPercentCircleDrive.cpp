#include "AutoPercentCircleDrive.h"

AutoPercentCircleDrive::AutoPercentCircleDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double percentCircle) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_radius = radius;
	m_outerSpeed = outerSpeed;
	m_direction = direction;
	m_percentCircle = percentCircle;

}

// Called just before this Command runs the first time
void AutoPercentCircleDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoPercentCircleDrive::Execute() {
	double middleCircumference = 2 * M_PI * m_radius;
	double partCircleDrive = middleCircumference / m_percentCircle;
	AutoDrive(m_radius, m_outerSpeed, m_direction, partCircleDrive);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoPercentCircleDrive::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void AutoPercentCircleDrive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoPercentCircleDrive::Interrupted() {

}
