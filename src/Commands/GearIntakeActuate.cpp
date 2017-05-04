#include "GearIntakeActuate.h"
#include "Robot.h"

GearIntakeActuate::GearIntakeActuate(frc::DoubleSolenoid::Value SolenoidDirection) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::gear.get());
	m_SolenoidDirection = SolenoidDirection;
}

// Called just before this Command runs the first time
void GearIntakeActuate::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearIntakeActuate::Execute() {
		Robot::gear->ActuateGearIntake(m_SolenoidDirection);
}

// Make this return true when this Command no longer needs to run execute()
bool GearIntakeActuate::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void GearIntakeActuate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearIntakeActuate::Interrupted() {

}
