#include "AutoDimeSpin.h"

AutoDimeSpin::AutoDimeSpin(double speed, double turnDistance, Drivetrain::Direction direction) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	m_speed = speed;
	m_direction = direction;
	m_turnDistance = turnDistance;
}

// Called just before this Command runs the first time
void AutoDimeSpin::Initialize() {
	//resets the encoder before we start
	Robot::drivetrain->ResetEncoders();
}

// Called repeatedly when this Command is scheduled to run
void AutoDimeSpin::Execute() {
	//spins the robot on a dime using the inputed speed
	switch(m_direction) {
		case Drivetrain::Direction::clockwise:
			Robot::drivetrain->DriveRobotTank(m_speed, -m_speed);
			break;
		case Drivetrain::Direction::counterClockwise:
			Robot::drivetrain->DriveRobotTank(-m_speed, m_speed);
			break;
		default:
			Robot::drivetrain->DriveRobotTank(0.0, 0.0);
			std::cout << "That direction isn't an option" << std::endl;

	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDimeSpin::IsFinished() {
	//determines if the robot  is done turning based off of reading the encoders
	double leftDistance = abs(Robot::drivetrain->GetLeftEncoder());
		double rightDistance = abs(Robot::drivetrain->GetRightEncoder());
		if(abs(leftDistance - rightDistance) > 2) {
			//set lagging encoder to value of other encoder
			if(leftDistance > rightDistance) {
				rightDistance = leftDistance;
			}else{
				leftDistance = rightDistance;
			}
		}
		return (rightDistance + leftDistance) >= m_turnDistance;
}

// Called once after isFinished returns true
void AutoDimeSpin::End() {
	//turns off the motors when we're done
	Robot::drivetrain->DriveRobotTank(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDimeSpin::Interrupted() {

}
