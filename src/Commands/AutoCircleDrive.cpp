#include "AutoCircleDrive.h"

AutoCircleDrive::AutoCircleDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double degrees) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	//quick declares for the inputed values
	m_leftSpeed = 0.0;
	m_rightSpeed = 0.0;
	m_direction = direction;
	m_degrees = degrees;
	m_radius = radius;
	int width = 27;
	//calculating the speed the inner wheels need to spin at to drive in a circle with the inputed radius
	double innerSpeed = ((m_radius - (width / 2)) / (m_radius + (width/2)) * outerSpeed);
	std::cout << "Inner speed: " << innerSpeed << std::endl;
	switch (m_direction) {
	//determining which is the inner side and which is the outer side for the wheels
		case Drivetrain::Direction::clockwise:
			m_leftSpeed = outerSpeed;
			m_rightSpeed = innerSpeed;
			break;
		case Drivetrain::Direction::counterClockwise:
			m_leftSpeed = innerSpeed;
			m_rightSpeed = outerSpeed;
			break;
		default:
			std::cout << "That direction isn't an option in the AutoDrive constructor: " << (int)m_direction << std::endl;
			m_leftSpeed = 0.0;
			m_rightSpeed = 0.0;
	}
	std::cout << m_leftSpeed << std::endl;
	std::cout << m_rightSpeed << std::endl;
}

// Called just before this Command runs the first time
void AutoCircleDrive::Initialize() {
	//reseting the encoders before we start
	Robot::drivetrain->ResetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void AutoCircleDrive::Execute() {
	//drives the robot in a circle using the speeds figured out in the constructor
	Robot::drivetrain->DriveRobotTank(m_leftSpeed, m_rightSpeed);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoCircleDrive::IsFinished() {
	//seeing if the robot is done turning based off of reading the encoders
	double feetsGone;
	double middleCircumference = 2.0 * M_PI * m_radius;
	double partOfCircle = m_degrees / 360.0;
	double partToDrive = middleCircumference * partOfCircle;
	std::cout << "Circumference: " << middleCircumference << std::endl;
	std::cout << "Part of Circle to Drive: " << partOfCircle << std::endl;
	std::cout << "Part to drive: " << partToDrive << std::endl;
	switch (m_direction) {
		case Drivetrain::Direction::clockwise:
			feetsGone = Robot::drivetrain->GetLeftEncoder();
			return feetsGone >= partToDrive;
			break;
		case Drivetrain::Direction::counterClockwise:
			feetsGone = Robot::drivetrain->GetRightEncoder();
			return feetsGone >= partToDrive;
			break;
		default:
			std::cout << "That direction isn't an option in the AutoDrive finished: " << (int)m_direction << std::endl;
			return true;
	}
}

// Called once after isFinished returns true
void AutoCircleDrive::End() {
	//turns off the motors when we're done
	Robot::drivetrain->DriveRobotTank(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoCircleDrive::Interrupted() {

}
