#include "AutoDrive.h"

AutoDrive::AutoDrive(double radius, double outerSpeed, Drivetrain::Direction direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_radius = radius;
	m_outerSpeed = outerSpeed;
	m_direction = direction;
	m_leftSpeed = 0.0;
	m_rightSpeed = 0.0;
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {
	m_leftSpeed = Robot::drivetrain->AutoCalcSpeeds(m_radius, m_outerSpeed, m_direction).leftSpeed;
	m_rightSpeed = m_leftSpeed = Robot::drivetrain->AutoCalcSpeeds(m_radius, m_outerSpeed, m_direction).rightSpeed;
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
	Robot::drivetrain->DriveRobotTank(m_leftSpeed, m_rightSpeed);
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
