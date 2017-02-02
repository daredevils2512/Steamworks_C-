#include "ShooterVisionTrack.h"
#include "ShooterVisionScan.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Pixy.h"
#include "../Subsystems/Shooter.h"

ShooterVisionTrack::ShooterVisionTrack() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ShooterVisionTrack::Initialize() {
	Robot::shooter->SetSwivelSpeed(0);
}

// Called repeatedly when this Command is scheduled to run
void ShooterVisionTrack::Execute() {
	Pixy::ObjectValues trackedObj;
	if(RobotMap::shooterPixy->GetFrameSize() == 1){
		trackedObj = Robot::shooter->GetObjectData(0).GetValue();
	}else if(RobotMap::shooterPixy->GetFrameSize() > 1) {
		for(int i = 0; i < RobotMap::shooterPixy->GetFrameSize(); i++){
			if(i == 0){
				trackedObj = Robot::shooter->GetObjectData(0).GetValue();
			}else{
				Pixy::ObjectValues stare = Robot::shooter->GetObjectData(i).GetValue();
				if(trackedObj.y < stare.y){
					trackedObj = stare;
				}
			}
		}
	}else{
		return;
	}
	int middle = 318/2;
	int tolerance = trackedObj.width/2;
	double minspeed = 0.1;
	double maxspeed = 0.5;
	double speed = minspeed+((Robot::shooter->GetVirtualDistance(trackedObj)/120) * (maxspeed - minspeed));
	if(middle-tolerance <= trackedObj.x && trackedObj.x <= middle + tolerance){
		Robot::shooter->SetSwivelSpeed(0.0);
	}else if(trackedObj.x < middle){
		// left of middle
		Robot::shooter->SetSwivelSpeed(speed);
	}else{
		// hopefully to the right of middle
		Robot::shooter->SetSwivelSpeed(-speed);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionTrack::IsFinished() {
	return RobotMap::shooterPixy->GetFrameSize() == 0;
}

// Called once after isFinished returns true
void ShooterVisionTrack::End() {
	Robot::shooter->SetCurrentCommand(new ShooterVisionScan());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionTrack::Interrupted() {

}
