#include "GearToggleIntake.h"
#include "../Robot.h"

GearToggleIntake::GearToggleIntake() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void GearToggleIntake::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearToggleIntake::Execute() {
	if(Robot::gear->GetIntakeDirection() == frc::DoubleSolenoid::kForward) {
		Robot::gear->ActuateGearIntake(frc::DoubleSolenoid::kReverse);
	}else{
		Robot::gear->ActuateGearIntake(frc::DoubleSolenoid::kForward);;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool GearToggleIntake::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void GearToggleIntake::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearToggleIntake::Interrupted() {

}
