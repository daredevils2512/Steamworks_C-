#include "ShooterVisionScan.h"
#include "ShooterVisionTrack.h"
#include "../Robot.h"
#include "../Subsystems/Shooter.h"

ShooterVisionScan::ShooterVisionScan() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShooterVisionScan::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterVisionScan::Execute() {
	if (Robot::shooter->IsLeftLimitSwitchPressed()) {
		Robot::shooter->SetSwivelSpeed(0.3);
	}
	else if (Robot::shooter->IsRightLimitSwitchPressed()) {
		Robot::shooter->SetSwivelSpeed(-0.3);
	}
	else {
		Robot::shooter->SetSwivelSpeed(0.0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionScan::IsFinished() {
	return Robot::shooter->GetObjectData(0).HasValue();
}

// Called once after isFinished returns true
void ShooterVisionScan::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionScan::Interrupted() {

}
