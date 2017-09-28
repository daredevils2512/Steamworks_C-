#include "GearVisionTurn.h"
#include <cmath>

GearVisionTurn::GearVisionTurn(double targetX) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::gear.get());
	Requires(Robot::drivetrain.get());
	m_targetX = targetX;
	targetAcquired = false;
	abort = false;
	goalPixel = targetX;
	numberOfNegOne = 0;
	SetTimeout(1.0);
}

// Called just before this Command runs the first time
void GearVisionTurn::Initialize() {
	//resets all of our counters and booleans so we can start tracking
	targetAcquired = false;
	abort = false;
	numberOfNegOne = 0;
	std::cout << "start gear tracking" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void GearVisionTurn::Execute() {
	//Gets the frame data from the GearPixy so we can use it
	double targetX = 320;
	if(VisionServer::targets.size() > 0){
		targetX = 0;
		std::cout<<"Objects exist."<<std::endl;
		for(size_t i = 0; i < VisionServer::targets.size(); i++){
			std::cout<<"evaluating target..."<<std::endl;
			double thisX = VisionServer::targets[0].x;
			if(thisX > targetX){
				std::cout<<"new working x: " << thisX <<std::endl;
				targetX = thisX;
			}else{
				std::cout<<"too small x: " << thisX <<std::endl;
			}
		}
	}
	if(targetX == -1) {
		std::cout << "-1" << std::endl;
		numberOfNegOne++;
		if(numberOfNegOne >= 20) {
			abort = true;
			std::cout << "gear tracking aborted" << std::endl;
		}
	}else{
		numberOfNegOne = 0;
		TrackObject(targetX);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool GearVisionTurn::IsFinished() {
	return targetAcquired || abort || IsTimedOut();
}

// Called once after isFinished returns true
void GearVisionTurn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearVisionTurn::Interrupted() {
	End();
}

int GearVisionTurn::CenterXFinder(double obj1, double obj2, double xDiff) {
	int centerX = 159;
	if (obj1 > obj2) {
		centerX = obj1 - xDiff;
	} else if (obj2 > obj1) {
		centerX = obj2 - xDiff;
	}
	return centerX;
}

bool GearVisionTurn::IsHeightSame(double obj1, double obj2, double threshold) {
	//checking if the height of two objects is the same
	return Robot::drivetrain->IsWithinThreshold(obj1, obj2, threshold);
}

bool GearVisionTurn::IsYSame(double obj1, double obj2, double threshold) {
	//checking if the center y-coordinates of two objects are the same
	return Robot::drivetrain->IsWithinThreshold(obj1, obj2, threshold);
}

void GearVisionTurn::TrackObject(double objectX) {
	//vision tracks an object using the gear pixy by going until it finds the centerX coordinate inputed
	std::cout << objectX << std::endl;
	int tolerance = 8;
	int slowDownTolerance = 100;
	//checking if the object found has a centerX coordinate that is more or less the same as the target one
	if(goalPixel-(tolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
		Robot::drivetrain->DriveRobotTank(0.0, 0.0);
		std::cout << "Gear target acquired" << std::endl;
		targetAcquired = true;
	}else if(objectX < goalPixel) {
		//checking if the object found has a centerX coordinate that is to the right of the target coordinate
		if(goalPixel - (slowDownTolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
			std::cout << "slow" << std::endl;
			Robot::drivetrain->DriveRobotTank(-0.55, 0.55); //0.5
		}else{
			Robot::drivetrain->DriveRobotTank(-0.7, 0.7);
		}
		std::cout << "-" << std::endl;
	}else{
		//checking if the object found has a centerX coordinate that is to the left of the target coordinate
		if(goalPixel - (slowDownTolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
			Robot::drivetrain->DriveRobotTank(0.55, -0.55); //0.5
			std::cout << "slow" << std::endl;
		}else{
			Robot::drivetrain->DriveRobotTank(0.7, -0.7);
		}
		std::cout << "+" << std::endl;
	}
}
