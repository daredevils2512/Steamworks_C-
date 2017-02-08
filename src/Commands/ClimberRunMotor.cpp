#include "ClimberRunMotor.h"

ClimberRunMotor::ClimberRunMotor(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::climber.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ClimberRunMotor::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberRunMotor::Execute() {
	//Sets the speed of the climberMotor
	Robot::climber->SetSpeed(m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberRunMotor::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ClimberRunMotor::End() {
	//Turns the motor off
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberRunMotor::Interrupted() {
	End();
}
