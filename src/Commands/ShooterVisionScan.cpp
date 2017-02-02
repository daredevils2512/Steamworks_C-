#include "ShooterVisionScan.h"
#include "ShooterVisionTrack.h"
#include "../Robot.h"
#include "../Subsystems/Shooter.h"

ShooterVisionScan::ShooterVisionScan() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	speed = 0.15;
}

// Called just before this Command runs the first time
void ShooterVisionScan::Initialize() {
	Robot::shooter->SetSwivelSpeed(speed);
}

// Called repeatedly when this Command is scheduled to run
void ShooterVisionScan::Execute() {
	if (Robot::shooter->IsLeftLimitSwitchPressed() ||
			Robot::shooter->IsRightLimitSwitchPressed()) {
		speed = -speed; //reverse the speed

	}
	Robot::shooter->SetSwivelSpeed(speed);
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionScan::IsFinished() {
	return Robot::shooter->GetObjectData(0).HasValue();
}

// Called once after isFinished returns true
void ShooterVisionScan::End() {
	Robot::shooter->SetCurrentCommand(new ShooterVisionTrack());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionScan::Interrupted() {

}
