#include "AutoDrive.h"

AutoDrive::AutoDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double degrees) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_leftSpeed = 0.0;
	m_rightSpeed = 0.0;
	m_direction = direction;
	m_degrees = degrees;
	m_radius = radius;
	int width = 27;
	double innerSpeed = ((m_radius - width / 2) / (m_radius + width/2) * outerSpeed);
	switch (m_direction) {
		case Drivetrain::Direction::clockwise:
			m_leftSpeed = outerSpeed;
			m_rightSpeed = innerSpeed;
			break;
		case Drivetrain::Direction::counterClockwise:
			m_leftSpeed = innerSpeed;
			m_rightSpeed = outerSpeed;
			break;
		case Drivetrain::Direction::straight:
			m_leftSpeed = outerSpeed;
			m_rightSpeed = outerSpeed;
			break;
		default:
			std::cout << "That direction isn't an option in the AutoDrive constructor: " << (int)m_direction << std::endl;
			m_leftSpeed = 0.0;
			m_rightSpeed = 0.0;
	}
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
	Robot::drivetrain->DriveRobotTank(m_leftSpeed, m_rightSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() {
	double feetsGone;
	double leftDistance = abs(Robot::drivetrain->GetLeftEncoder());
	double rightDistance = abs(Robot::drivetrain->GetRightEncoder());
	double middleCircumference = 2 * M_PI * m_radius;
	double degreesToDrive = middleCircumference / m_degrees;
	switch (m_direction) {
		case Drivetrain::Direction::clockwise:
			feetsGone = Robot::drivetrain->GetLeftEncoder();
			return (degreesToDrive >= feetsGone);
			break;
		case Drivetrain::Direction::counterClockwise:
			feetsGone = Robot::drivetrain->GetRightEncoder();
			return (degreesToDrive >= feetsGone);
			break;
		case Drivetrain::Direction::straight:
			feetsGone = Robot::drivetrain->GetEncoders();
			if(abs(leftDistance - rightDistance) > 2) {
				//set lagging encoder to value of other encoder
				if(leftDistance > rightDistance) {
					rightDistance = leftDistance;
				}else{
					leftDistance = rightDistance;
				}
			}
			return (((leftDistance + rightDistance) / 2) > feetsGone);
			break;
		default:
			std::cout << "That direction isn't an option in the AutoDrive finished: " << (int)m_direction << std::endl;
			return true;
	}
}

// Called once after isFinished returns true
void AutoDrive::End() {
	Robot::drivetrain->DriveRobotTank(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {

}
