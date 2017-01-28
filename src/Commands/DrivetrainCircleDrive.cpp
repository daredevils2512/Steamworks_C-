#include <Commands/DrivetrainCircleDrive.h>

DrivetrainCircleDrive::DrivetrainCircleDrive(double actualRadius, bool direction, double distance, double outerVelocity) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
	//Setting the inputed numbers to different names that all start with m_ meaning they are declared as members of the command
	m_actualRadius = actualRadius;
	m_direction = direction;
	m_distance = distance;
	m_outerVelocity = outerVelocity;
}

// Called just before this Command runs the first time
void DrivetrainCircleDrive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void DrivetrainCircleDrive::Execute() {
	//Calling the function we created in the Drivetrain subsystem
	Robot::drivetrain->DriveCircle(m_actualRadius, m_direction, m_distance, m_outerVelocity);
}

// Make this return true when this Command no longer needs to run execute()
bool DrivetrainCircleDrive::IsFinished() {
	//Turning it off after the command is run because we don't want it to run over and over again
	return true;
}

// Called once after isFinished returns true
void DrivetrainCircleDrive::End() {
	//Tells the robot to stop driving in circles
	Robot::drivetrain->DriveCircle(0.0, true, 0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DrivetrainCircleDrive::Interrupted() {

}
