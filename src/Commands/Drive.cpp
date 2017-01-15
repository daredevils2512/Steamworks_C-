#include "Drive.h"
#include "OI.h"

Drive::Drive(double move , double turn) : Command() {
	m_move = move;
	m_turn = turn;
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::drivetrain.get());
}

// Called just before this Command runs the first time
void Drive::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {
		Robot::drivetrain->DriveRobot(Robot::oi->GetX() , Robot::oi->GetY());
	}


// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Drive::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {

}
