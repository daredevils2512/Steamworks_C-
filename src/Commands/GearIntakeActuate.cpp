#include "GearIntakeActuate.h"
#include "Robot.h"

GearIntakeActuate::GearIntakeActuate(bool SolenoidDirection) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_SolenoidDirection = SolenoidDirection;
}

// Called just before this Command runs the first time
void GearIntakeActuate::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearIntakeActuate::Execute() {
	if(m_SolenoidDirection) {
		Robot::gear->ActuateGearIntake(DoubleSolenoid::kForward);
	}
	else {
		Robot::gear->ActuateGearIntake(DoubleSolenoid::kReverse);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool GearIntakeActuate::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void GearIntakeActuate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearIntakeActuate::Interrupted() {

}
