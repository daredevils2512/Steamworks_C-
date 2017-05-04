#include "ClimberDisableCurrentLimit.h"
#include "../RobotMap.h"

ClimberDisableCurrentLimit::ClimberDisableCurrentLimit() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ClimberDisableCurrentLimit::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ClimberDisableCurrentLimit::Execute() {
	RobotMap::climberMotor->EnableCurrentLimit(false);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberDisableCurrentLimit::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ClimberDisableCurrentLimit::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberDisableCurrentLimit::Interrupted() {

}
