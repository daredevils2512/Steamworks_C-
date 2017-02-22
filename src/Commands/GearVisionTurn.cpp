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
}

// Called just before this Command runs the first time
void GearVisionTurn::Initialize() {
	targetAcquired = false;
	abort = false;
}

// Called repeatedly when this Command is scheduled to run
void GearVisionTurn::Execute() {
	//Gets the frame data from the GearPixy so we can use it
	std::vector<PixySubsystem::ObjectValues> objectsFound;
	objectsFound = Robot::pixySubsystem->GetGearPixyData();
	if(objectsFound.size() == 0){
		std::cout << "ERROR: No Gear Target Found" << std::endl;
		abort = true;
		return;
	}else if(objectsFound.size() == 1) {
		PixySubsystem::ObjectValues targetObject;
		targetObject = objectsFound[0];
		TrackObject(targetObject.x);
		std::cout << "One target found" << std::endl;
	}else{
		PixySubsystem::ObjectValues targetObject;
		int furthestLeftObjectPixel = 318;
		for(auto object : objectsFound) {
			if(object.x < furthestLeftObjectPixel) {
				targetObject = object;
				furthestLeftObjectPixel = object.x;
			}
		}
		TrackObject(targetObject.x);
		std::cout << "Found multiple targets" << std::endl;
	}


//	std::vector<PixySubsystem::ObjectValues> objectsFound;
//	objectsFound = Robot::pixySubsystem->GetGearPixyData();
//	//Creates the empty objects we will use to store object data
//	PixySubsystem::ObjectValues trackedObj1;
//	PixySubsystem::ObjectValues trackedObj2;
//	PixySubsystem::ObjectValues trackedObj3;
//	PixySubsystem::ObjectValues combinedObj;
//	//Creating the empty doubles for different values
//	//xDiff is the difference between the two objects found
//	//centerX is the centerX pixel between the two objects
//	//centerX defaults to 159 because it is the centerX pixel of the image
//	//heightSame is the check to see if the objects have the relatively same height in pixels
//	//heightSame defaults to false so that it won't drive unless it becomes true
//	double xDiff;
//	double centerX = 159;
//	bool heightSame = false;
//	if(Robot::pixySubsystem->GetFrameSize() == 2) {
//		trackedObj1 = objectsFound[0];
//		trackedObj2 = objectsFound[1];
//		xDiff = abs(trackedObj1.x - trackedObj2.x);
//		centerX = CenterXFinder(trackedObj1.x, trackedObj2.x, xDiff);
//		heightSame = IsHeightSame(trackedObj1.height, trackedObj2.height, 5);
//		if(heightSame == true && IsYSame(trackedObj1.y, trackedObj2.y, 5)) {
//			TurnDirection(m_targetX, centerX);
//		}
//	} else if(Robot::pixySubsystem->GetFrameSize() > 2) {
//		for(int i = 0; i < Robot::pixySubsystem->GetFrameSize(); i++) {
//			if(i == 0) {
//				trackedObj1 = objectsFound[0];
//			} else if(i == 1) {
//				trackedObj2 = objectsFound[1];
//				xDiff = abs(trackedObj1.x - trackedObj2.x);
//				centerX = CenterXFinder(trackedObj1.x, trackedObj2.x, xDiff);
//				heightSame = IsHeightSame(trackedObj1.height, trackedObj2.height, 5);
//				if(heightSame == true && IsYSame(trackedObj1.y, trackedObj2.y, 5)) {
//					TurnDirection(m_targetX, centerX);
//				}
//			} else if(i == 2) {
//				trackedObj3 = objectsFound[2];
//				if(Robot::drivetrain->IsWithinThreshold(trackedObj1.x, trackedObj2.x, 10)) {
//					combinedObj.x = trackedObj2.x;
//					xDiff = abs(combinedObj.x - trackedObj3.x);
//					centerX = CenterXFinder(combinedObj.x, trackedObj3.x, xDiff);
//				} else if(Robot::drivetrain->IsWithinThreshold(trackedObj1.x, trackedObj3.x, 10)) {
//					combinedObj.x = trackedObj3.x;
//					xDiff = abs(combinedObj.x - trackedObj2.x);
//					centerX = CenterXFinder(combinedObj.x, trackedObj2.x, xDiff);
//				} else if(Robot::drivetrain->IsWithinThreshold(trackedObj2.x, trackedObj3.x, 10)) {
//					combinedObj.x = trackedObj2.x;
//					xDiff = abs(combinedObj.x - trackedObj1.x);
//					centerX = CenterXFinder(combinedObj.x, trackedObj1.x, xDiff);
//				}
//				heightSame = IsHeightSame(trackedObj1.height, trackedObj2.height, 10);
//				if(heightSame == true && IsYSame(trackedObj1.y, trackedObj2.y, 10)) {
//					TurnDirection(m_targetX, centerX);
//				}
//			}
//		}
//	}
}

// Make this return true when this Command no longer needs to run execute()
bool GearVisionTurn::IsFinished() {
	return targetAcquired || abort;
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
	return Robot::drivetrain->IsWithinThreshold(obj1, obj2, threshold);
}

bool GearVisionTurn::IsYSame(double obj1, double obj2, double threshold) {
	return Robot::drivetrain->IsWithinThreshold(obj1, obj2, threshold);
}

void GearVisionTurn::TurnDirection(double m_targetX , double centerX){
	double error = centerX - m_targetX;
	error = error * 0.005;
	if (error > 0.5) {
		error = 0.5;
	} else if (error < -0.5){
		error = -0.5;
	}
	if(Robot::drivetrain->IsWithinThreshold(m_targetX, centerX, 5)) {
		Robot::drivetrain->DriveRobotTank(0.5, 0.0);
	} else if(centerX != m_targetX) {
		Robot::drivetrain->DriveRobotTank(0.0, error);
	} else {
		Robot::drivetrain->DriveRobotTank(0.0, 0.0);
	}
}

void GearVisionTurn::TrackObject(double objectX) {
	int tolerance = 20;
	if(goalPixel-(tolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
		Robot::drivetrain->DriveRobotTank(0.0, 0.0);
		std::cout << "Gear target acquired" << std::endl;
		targetAcquired = true;
	}else if(objectX < goalPixel) {
		Robot::drivetrain->DriveRobotTank(-0.8, 0.8);
		std::cout << "-" << std::endl;
	}else{
		Robot::drivetrain->DriveRobotTank(0.8, -0.8);
		std::cout << "+" << std::endl;
	}
}
