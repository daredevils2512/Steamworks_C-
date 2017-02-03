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
bool ShooterVisionTrack::IsWithinThreshold(double setpoint, double threshold, double value){
	double tol = threshold / 2;
	return setpoint-tol <= value && value <= setpoint + tol;
}
// Called repeatedly when this Command is scheduled to run
void ShooterVisionTrack::Execute() {
	Pixy::ObjectValues trackedObj;
	bool trackedSet = false;
	Pixy::ObjectValues topBar;
	bool barsSet = false;
	Pixy::ObjectValues bottomBar;
	if(RobotMap::shooterPixy->GetFrameSize() == 1){
		trackedObj = Robot::shooter->GetObjectData(0).GetValue();
	}else if(RobotMap::shooterPixy->GetFrameSize() > 1) {
		int maxArea = 79.5 * 49.5;
		//sets max area by dividing the image frame by 4
		for(int i = 0; i < RobotMap::shooterPixy->GetFrameSize(); i++){
			Pixy::ObjectValues stare = Robot::shooter->GetObjectData(i).GetValue(); //focused object
			if(stare.width * stare.height < maxArea){
				for(int j = 0; j < RobotMap::shooterPixy->GetFrameSize(); j++){
					if(j != i){
						Pixy::ObjectValues pSecBar = Robot::shooter->GetObjectData(j).GetValue();
						if(barsSet){
							if(topBar.y > pSecBar.y || topBar.y > stare.y){
								//if the top object's y value is greater than the potential secondary or the top object's y is greater
								//than the focused object, then continue
								continue;
							}
						}
						if(IsWithinThreshold(stare.x,5,pSecBar.x)){
							//checks to see if x value of the focused object and potential interferring object's x values are similiar
							if(stare.y > pSecBar.y){
								topBar = stare;
								bottomBar = pSecBar;
							}else{
								topBar = pSecBar;
								bottomBar = stare;
							}
							barsSet = true;
						}
					}
				}
				if(!trackedSet){
					trackedObj = stare;
					trackedSet = true;
				}else{
					if(trackedObj.y < stare.y){
						trackedObj = stare;
					}
				}
			}
		}
	}else{
		return;
	}
	//sets the center of the image
	int middle = 318/2;
	//sets the acceptable tolerance of the target
	int tolerance = trackedObj.width/2;
	//sets the minimum and maximum speeds of the turret swivel
	double minspeed = 0.1;
	double maxspeed = 0.5;
	double speed = minspeed+((Robot::shooter->GetVirtualDistance(trackedObj)/120) * (maxspeed - minspeed));
	if(middle-tolerance <= trackedObj.x && trackedObj.x <= middle + tolerance){
		//if the difference between the center and the tolerance is less than or equal to the middle added to the tolerance
		//then stop the shooter from swiveling
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
	//ends the command if the frame size is zero or if a limit switch is pressed
	return RobotMap::shooterPixy->GetFrameSize() == 0 || RobotMap::shooterLeftLimitSwitch->Get() || RobotMap::shooterRightLimitSwitch->Get();
}

// Called once after isFinished returns true
void ShooterVisionTrack::End() {
	//once the command is over the new command it moves to is vision scan to reaquire a target
	Robot::shooter->SetCurrentCommand(new ShooterVisionScan());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionTrack::Interrupted() {

}
