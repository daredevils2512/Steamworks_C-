#include "AutoDrive.h"

AutoDrive::AutoDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double targetFeet) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_leftSpeed = 0.0;
	m_rightSpeed = 0.0;
	m_targetFeet = targetFeet;
	m_direction = direction;
	int width = 27;
	double innerSpeed = ((radius - width / 2) / (radius + width/2) * outerSpeed);
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
	switch (m_direction) {
		case Drivetrain::Direction::clockwise:
			feetsGone = Robot::drivetrain->GetLeftEncoder();
			break;
		case Drivetrain::Direction::counterClockwise:
			feetsGone = Robot::drivetrain->GetRightEncoder();
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
			return (((leftDistance + rightDistance) / 2) > m_targetFeet);
			break;
		default:
			std::cout << "That direction isn't an option in the AutoDrive finished: " << (int)m_direction << std::endl;
			return true;
	}
	return (feetsGone >= m_targetFeet);
}

// Called once after isFinished returns true
void AutoDrive::End() {
	Robot::drivetrain->DriveRobotTank(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {

}
