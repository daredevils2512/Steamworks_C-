#include "FloorIntakeRunMotor.h"

FloorIntakeRunMotor::FloorIntakeRunMotor(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::floorIntake.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void FloorIntakeRunMotor::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void FloorIntakeRunMotor::Execute() {
	//turns on the floor intake at the inputed speed
	Robot::floorIntake->SetSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool FloorIntakeRunMotor::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void FloorIntakeRunMotor::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FloorIntakeRunMotor::Interrupted() {
	End();
}
