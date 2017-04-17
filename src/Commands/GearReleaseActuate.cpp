#include "GearReleaseActuate.h"
#include "Robot.h"

GearReleaseActuate::GearReleaseActuate(frc::DoubleSolenoid::Value SolenoidDirection) {
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::gear.get());
	m_SolenoidDirection = SolenoidDirection;
}

// Called just before this Command runs the first time
void GearReleaseActuate::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearReleaseActuate::Execute() {
		Robot::gear->ActuateGearRelease(m_SolenoidDirection);
}

// Make this return true when this Command no longer needs to run execute()
bool GearReleaseActuate::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void GearReleaseActuate::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearReleaseActuate::Interrupted() {

}
