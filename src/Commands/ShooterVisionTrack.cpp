#include "ShooterVisionTrack.h"
#include "ShooterVisionTrack.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Subsystems/Shooter.h"
#include "../Subsystems/PixySubsystem.h"

ShooterVisionTrack::ShooterVisionTrack() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	abort = false;
	speed = 1;
	fwdLastPressed = false;
	revLastPressed = false;
	fwdLastPassed = false;
	revLastPassed = false;
}

// Called just before this Command runs the first time
void ShooterVisionTrack::Initialize() {
//	Robot::shooter->SetSwivelSpeed(0);
}

bool ShooterVisionTrack::IsWithinThreshold(double setpoint, double threshold, double value){
	double tol = threshold / 2;
	return setpoint-tol <= value && value <= setpoint + tol;
}

// Called repeatedly when this Command is scheduled to run
void ShooterVisionTrack::Execute() {
	std::vector<PixySubsystem::ObjectValues> frame = Robot::pixySubsystem->GetShooterPixyData();
	if(frame.size() == 0){
		if ( FwdPressedThisTime() || FwdEncPassedThisTime()||
				RevPressedThisTime() || RevEncPassedThisTime()) {
			speed = -speed; //reverse the speed

		}
		Robot::shooter->SetSwivelSpeed(speed);
		return;
	}

	PixySubsystem::ObjectValues trackedObj;
	bool trackedSet = false;
	PixySubsystem::ObjectValues topBar;
	bool barsSet = false;
	PixySubsystem::ObjectValues bottomBar;
	int maxArea = 79.5 * 49.5;
	if(frame.size() == 1){ // if we have one object
		PixySubsystem::ObjectValues stare = frame[0]; // focused object
		if(stare.width*stare.height < maxArea){// if the object is smaller than the maximum area
			trackedObj = stare;
			trackedSet = true;
		}
		abort = !trackedSet; // abort if we haven't set tracked
		if(abort){
			return; // if not tracked, abort!
		}
	}else if(frame.size() > 1) {
		// we have multiple objects
		// sets max area by dividing the image frame by 4
		for(unsigned i = 0; i < frame.size(); i++){
			//iterate through all known objects
			PixySubsystem::ObjectValues stare = frame[i]; //focused object
			if(stare.width * stare.height < maxArea){
				// if this current object is within the area maximum
				for(unsigned j = i+1; j < frame.size(); j++){
					// iterate through all objects that haven't been "checked"
					PixySubsystem::ObjectValues pSecBar = frame[j];
					if(pSecBar.width * pSecBar.height >= maxArea){
						//if this object doesn't match max area checks, skip this iteration
						continue;
					}
					if(barsSet){
						//if bars have been set.
						if(topBar.y > pSecBar.y || topBar.y > stare.y){
							//if the top object's y value is greater than the potential secondary or the top object's y is greater
							//than the focused object, then skip this iteration
							continue;
						}
					}
					if(IsWithinThreshold(stare.x,5,pSecBar.x)){
						//checks to see if x value of the focused object and potential interferring object's x values are similiar
						if(stare.y > pSecBar.y){
							//if the top bar is stare...
							topBar = stare;
							bottomBar = pSecBar;
						}else{
							//if the top bar isn't stare...
							topBar = pSecBar;
							bottomBar = stare;
						}
						barsSet = true;
					}
					//}
				}

				//fallback trackedSet
				if(!trackedSet){ // if tracked wasn't set (first iteration)
					trackedObj = stare;
					trackedSet = true;
				}else{// if tracked has been set before
					if(trackedObj.y < stare.y){ // If the last saved object is "under" this one...
						trackedObj = stare;/// ... overwrite it with this object
					}
				}
			}
		}
	}else{
		//if we have zero objects somehow, abort.
		abort = true;
		return;
	}
	if((!trackedSet && !barsSet) || frame.size() < 1){
		//if we don't have anything, abort!
		abort = true;
		return;
	}
	//sets the center of the image
	int middle = 318/2;
	//sets the acceptable tolerance of the target
	int tolerance = 6;
	//sets the minimum and maximum speeds of the turret swivel

	int dist = Robot::shooter->GetVirtualDistance(trackedObj);
	int dCenter = middle - trackedObj.x;
	//double minspeed = 0.1;
	//double maxspeed = 0.5;
	//double speed = minspeed+((dist/120) * (maxspeed - minspeed));
	double speed = 0.25;
	if(middle-(tolerance/2) <= trackedObj.x && trackedObj.x <= middle + (tolerance/2)){
		//if the difference between the center and the tolerance is less than or equal to the middle added to the tolerance
		//then stop the shooter from swiveling
		Robot::shooter->SetSwivelSpeed(0);
	}else if(trackedObj.x < middle){
		// left of middle
		Robot::shooter->SetSwivelSpeed(speed);
	}else{
		// hopefully to the right of middle
		Robot::shooter->SetSwivelSpeed(-speed);
	}

}
bool ShooterVisionTrack::FwdPressedThisTime() {
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
bool ShooterVisionTrack::RevPressedThisTime() {
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
bool ShooterVisionTrack::FwdEncPassedThisTime() {
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
bool ShooterVisionTrack::RevEncPassedThisTime() {
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

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionTrack::IsFinished() {
	//ends the command if the frame size is zer or if a limit switch is pressed
	return false;//abort || passedSafetyThreshold;
}

// Called once after isFinished returns true
void ShooterVisionTrack::End() {
	//once the command is over the new command it moves to is vision scan to require a target
	Robot::shooter->SetSwivelSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionTrack::Interrupted() {

}
