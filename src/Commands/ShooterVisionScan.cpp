#include "ShooterVisionScan.h"
#include "ShooterVisionTrack.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include "../Subsystems/Shooter.h"

ShooterVisionScan::ShooterVisionScan() {
	//Requires(Robot::shooter.get());
	// Use Requires() here to declare subsystem dependencies
	speed = 0.15;
	fwdLastPressed = false;
	revLastPressed = false;
}

// Called just before this Command runs the first time
void ShooterVisionScan::Initialize() {
	//Robot::shooter->SetSwivelSpeed(speed);
}

// Called repeatedly when this Command is scheduled to run
bool ShooterVisionScan::FwdPressedThisTime() {
	if(RobotMap::shooterTurretSwivel->IsFwdLimitSwitchClosed()){
		if(fwdLastPressed)
			return false;
		else{
			fwdLastPressed = true;
			return true;
		}

	}else{
		fwdLastPressed = false;
		return true;
	}
}
bool ShooterVisionScan::RevPressedThisTime() {
	if(RobotMap::shooterTurretSwivel->IsRevLimitSwitchClosed()){
		if(revLastPressed)
			return false;
		else{
			revLastPressed = true;
			return true;
		}
	}else{
		revLastPressed = false;
		return true;
	}
}
bool ShooterVisionScan::FwdEncPassedThisTime() {
	if(RobotMap::shooterTurretSwivel->GetEncPosition() > Robot::shooter->maxEncPosition){
		if(fwdLastPassed)
			return false;
		else{
			fwdLastPassed = true;
			return true;
		}

	}else{
		fwdLastPassed = false;
		return true;
	}
}
bool ShooterVisionScan::RevEncPassedThisTime() {
	if(RobotMap::shooterTurretSwivel->GetEncPosition() < -Robot::shooter->maxEncPosition){
		if(revLastPassed)
			return false;
		else{
			revLastPassed = true;
			return true;
		}
	}else{
		revLastPassed = false;
		return true;
	}
}
void ShooterVisionScan::Execute() {
	if ( FwdPressedThisTime() || FwdEncPassedThisTime()||
			RevPressedThisTime() || RevEncPassedThisTime()) {
		speed = -speed; //reverse the speed

	}
	Robot::shooter->SetSwivelSpeed(speed);

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionScan::IsFinished() {
	std::vector<PixySubsystem::ObjectValues> ob = Robot::pixySubsystem->GetShooterPixyData();
	return ob.size() > 0;
}

// Called once after isFinished returns true
void ShooterVisionScan::End() {
	(new ShooterVisionTrack)->Start();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionScan::Interrupted() {

}
