#include "GearVisionScan.h"
#include "GearVisionTurn.h"
#include "../Robot.h"
#include "../Subsystems/Shooter.h"

GearVisionScan::GearVisionScan(double targetX) {
	GearVisionScan::targetX = targetX;
	// Use Requires() here to declare subsystem dependencies
	Requires(Robot::gear.get());
}

// Called just before this Command runs the first time
void GearVisionScan::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearVisionScan::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool GearVisionScan::IsFinished() {
	return Robot::pixySubsystem->GetGearPixyData().size() > 0;
}

// Called once after isFinished returns true
void GearVisionScan::End() {
	Robot::shooter->SetCurrentCommand(new GearVisionTurn(targetX));
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearVisionScan::Interrupted() {

}
