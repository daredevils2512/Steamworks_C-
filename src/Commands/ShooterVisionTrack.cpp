#include "ShooterVisionTrack.h"
#include "ShooterVisionTrack.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Subsystems/Shooter.h"
#include "../Subsystems/PixySubsystem.h"

ShooterVisionTrack::ShooterVisionTrack(bool isAutonomous) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	abort = false;
	targetAcquired = false;
	m_isAutonomous = isAutonomous;
	speed = 0.4;
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
//	std::cout << "vector size" << frame.size() << std::endl;
//	std::cout << "speed: " << speed << std::endl;
	if(frame.size() == 0){
		targetAcquired = false;
//		if (/*FwdPressedThisTime() ||*/ FwdEncPassedThisTime() ||
//				/*RevPressedThisTime() ||*/ RevEncPassedThisTime()) {
////			std::cout << "switch speed" << std::endl;
//			speed = -speed; //reverse the speed
//
//		}
		if(FwdEncPassedThisTime()) {
			speed = -0.4;
		}
		if(RevEncPassedThisTime()) {
			speed = 0.4;
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
//		std::cout << "found one object" << std::endl;
		PixySubsystem::ObjectValues stare = frame[0]; // focused object
		if(stare.y > 90){
			return;
		}
		if(stare.width*stare.height < maxArea){// if the object is smaller than the maximum area
			trackedObj = stare;
			trackedSet = true;
		}
		abort = !trackedSet; // abort if we haven't set tracked
		if(abort){
//			std::cout << "aborted 1 object" << std::endl;
			return; // if not tracked, abort!
		}
	}else if(frame.size() > 1) {
		targetAcquired = false;
		// we have multiple objects
		// sets max area by dividing the image frame by 4
//		std::cout << "found multiple objects" << std::endl;
		for(unsigned i = 0; i < frame.size(); i++){
			//iterate through all known objects
			PixySubsystem::ObjectValues stare = frame[i]; //focused object
			if(stare.y > 90){
				continue;
			}
			if(stare.width * stare.height < maxArea){
				// if this current object is within the area maximum
				for(unsigned j = i+1; j < frame.size(); j++){
					// iterate through all objects that haven't been "checked"
					PixySubsystem::ObjectValues pSecBar = frame[j];
//					if(pSecBar.y > 100){
//						continue;
//					}
					if(pSecBar.width * pSecBar.height >= maxArea){
						//if this object doesn't match max area checks, skip this iteration
						continue;
					}
					if(pSecBar.y > 90){
						std::cout<<"SHOOTER: " << pSecBar.y << "px DOES NOT CONFORM TO CONSTRAINTS!" <<std::endl;
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
//		std::cout << "aborted zero objects" << std::endl;
		abort = true;
		return;
	}
	if((!trackedSet && !barsSet) || frame.size() < 1){
		//if we don't have anything, abort!
//		std::cout << "aborted we have nothing" << std::endl;
		abort = true;
		return;
	}
	//sets the center of the image
	int middle = 160;//159
	//sets the acceptable tolerance of the target
	int tolerance = 20;
	int slowDownTolerance = 150;
	//sets the minimum and maximum speeds of the turret swivel

	//double minspeed = 0.1;
	//double maxspeed = 0.5;
	//double speed = minspeed+((dist/120) * (maxspeed - minspeed));
	if(middle-(tolerance/2) <= trackedObj.x && trackedObj.x <= middle + (tolerance/2)){
		//if the difference between the center and the tolerance is less than or equal to the middle added to the tolerance
		//then stop the shooter from swiveling
		targetAcquired = true;
		Robot::shooter->SetSwivelSpeed(0);
		std::cout << trackedObj.x << std::endl;
//		std::cout << "tolerance acceptable" << std::endl;
	}else if(trackedObj.x < middle){
		// left of middle
//		std::cout << "-" << std::endl;
		targetAcquired = false;
		if(middle-(slowDownTolerance/2) <= trackedObj.x && trackedObj.x <= middle + (slowDownTolerance/2)) {
			Robot::shooter->SetSwivelSpeed(-0.2);
		}else{
			Robot::shooter->SetSwivelSpeed(-0.4);
		}
	}else{
		// hopefully to the right of middle
//		std::cout << "+" << std::endl;
		targetAcquired = false;
		if(middle-(slowDownTolerance/2) <= trackedObj.x && trackedObj.x <= middle + (slowDownTolerance/2)) {
			Robot::shooter->SetSwivelSpeed(0.2);
		}else{
			Robot::shooter->SetSwivelSpeed(0.4);
		}
	}
}
bool ShooterVisionTrack::FwdPressedThisTime() {
	if(RobotMap::shooterTurretSwivel->IsFwdLimitSwitchClosed()){
		if(fwdLastPressed){
			return false;
		}else{
			fwdLastPressed = true;
			//std::cout << "FwdPressedThisTime = true" << std::endl;
			return true;
		}

	}else{
		fwdLastPressed = false;
		//std::cout << "FwdPressedThisTime = false" << std::endl;
		return false;
	}
}
bool ShooterVisionTrack::RevPressedThisTime() {
	if(RobotMap::shooterTurretSwivel->IsRevLimitSwitchClosed()){
		if(revLastPressed){
			return false;
		}else{
			revLastPressed = true;
			//std::cout << "RevPressedThisTime = true" << std::endl;
			return true;
		}
	}else{
		revLastPressed = false;
		//std::cout << "RevPressedThisTime = false" << std::endl;
		return false;
	}
}
bool ShooterVisionTrack::FwdEncPassedThisTime() {
	if(RobotMap::shooterTurretSwivel->GetEncPosition() > Robot::shooter->maxEncPosition){
		if(fwdLastPassed)
			return false;
		else{
			fwdLastPassed = true;
			//std::cout << "FwdEncPassedThisTime = true" << std::endl;
			return true;
		}

	}else{
		fwdLastPassed = false;
		//std::cout << "FwdEncPassedThisTime = false" << std::endl;
		return false;
	}
}
bool ShooterVisionTrack::RevEncPassedThisTime() {
	if(RobotMap::shooterTurretSwivel->GetEncPosition() < -Robot::shooter->maxEncPosition){
		if(revLastPassed)
			return false;
		else{
			revLastPassed = true;
			//std::cout << "RevEncPassedThisTime = true" << std::endl;
			return true;
		}
	}else{
		revLastPassed = false;
		//std::cout << "RevEncPassedThisTime = false" << std::endl;
		return false;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionTrack::IsFinished() {
	//ends the command if the frame size is zer or if a limit switch is pressed
	if(m_isAutonomous) {
		return targetAcquired;
	}else{
		return false;//abort || passedSafetyThreshold;
	}
}

// Called once after isFinished returns true
void ShooterVisionTrack::End() {
	//once the command is over the new command it moves to is vision scan to require a target
	Robot::shooter->SetSwivelSpeed(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionTrack::Interrupted() {
	End();
}
