#include "GearVisionTurn.h"

GearVisionTurn::GearVisionTurn(double targetX) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::gear.get());
	Requires(Robot::drivetrain.get());
	m_targetX = targetX;
}

// Called just before this Command runs the first time
void GearVisionTurn::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void GearVisionTurn::Execute() {
	Robot::gear->UpdateObjectData();
	if(RobotMap::gearPixy->IsFrameEmpty()){
		return;

	}
	Pixy::ObjectValues trackedObj1;
	Pixy::ObjectValues trackedObj2;
	Pixy::ObjectValues trackedObj3;
	Pixy::ObjectValues combinedObj;
	double xDiff;
	double centerX = 159;
	bool heightSame = false;
	if(RobotMap::gearPixy->GetFrameSize() == 2) {
		trackedObj1 = Robot::gear->GetObjectData(0).GetValue();
		trackedObj2 = Robot::gear->GetObjectData(1).GetValue();
		xDiff = abs(trackedObj1.x - trackedObj2.x);
		if (trackedObj1.x > trackedObj2.x) {
			centerX = trackedObj1.x - xDiff;
		} else if (trackedObj2.x > trackedObj1.x) {
			centerX = trackedObj2.x - xDiff;
		}
		heightSame = IsHeightSame(trackedObj1.height, trackedObj2.height);
		if(heightSame == true && IsYSame(trackedObj1.y, trackedObj2.y)) {
			Robot::drivetrain->TurnDirection(m_targetX, centerX);
		}
		//Add checks with the height of the objects and the y-coordinates
		//Use the DriveRobot function instead

	} else if(RobotMap::gearPixy->GetFrameSize() > 2) {
		for(int i = 0; i < RobotMap::gearPixy->GetFrameSize(); i++) {
			if(i == 0) {
				trackedObj1 = Robot::gear->GetObjectData(0).GetValue();
			} else if(i == 1) {
				trackedObj2 = Robot::gear->GetObjectData(1).GetValue();
				xDiff = abs(trackedObj1.x - trackedObj2.x);
				if (trackedObj1.x > trackedObj2.x) {
					centerX = trackedObj1.x - xDiff;
				} else if (trackedObj2.x > trackedObj1.x) {
					centerX = trackedObj2.x - xDiff;
				}
				Robot::drivetrain->TurnDirection(m_targetX, centerX);
			} else if(i == 2) {
				trackedObj3 = Robot::gear->GetObjectData(2).GetValue();
				if(IsWithinThreshold(trackedObj1.x, trackedObj2.x, 10)) {
					combinedObj.x = trackedObj2.x;
					xDiff = abs(combinedObj.x - trackedObj3.x);
					centerX = CenterXFinder(combinedObj.x, trackedObj3.x, xDiff);
				} else if(IsWithinThreshold(trackedObj1.x, trackedObj3.x, 10)) {
					combinedObj.x = trackedObj3.x;
					xDiff = abs(combinedObj.x - trackedObj2.x);
					centerX = CenterXFinder(combinedObj.x, trackedObj2.x, xDiff);
				} else if(IsWithinThreshold(trackedObj2.x, trackedObj3.x, 10)) {
					combinedObj.x = trackedObj2.x;
					xDiff = abs(combinedObj.x - trackedObj1.x);
					centerX = CenterXFinder(combinedObj.x, trackedObj1.x, xDiff);
				}
				Robot::drivetrain->TurnDirection(m_targetX, centerX);
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool GearVisionTurn::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void GearVisionTurn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearVisionTurn::Interrupted() {

}

bool GearVisionTurn::IsWithinThreshold(double obj1X, double obj2X, int threshold){
	int tol = threshold / 2;
	return (obj1X - tol <= obj2X && obj1X + tol >= obj2X) && (obj2X - tol <= obj1X && obj2X + tol >= obj1X);
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

bool GearVisionTurn::IsHeightSame(double obj1, double obj2) {
	return IsWithinThreshold(obj1, obj2, 5);
}

bool GearVisionTurn::IsYSame(double obj1, double obj2) {
	return IsWithinThreshold(obj1, obj2, 5);
}
