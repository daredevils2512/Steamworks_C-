#include "GearVisionTurn.h"

GearVisionTurn::GearVisionTurn(double targetX) {
	isFinished = false;
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
	//Gets the frame data from the GearPixy so we can use it
	Robot::gear->UpdateObjectData();
	if(RobotMap::gearPixy->IsFrameEmpty()){
		isFinished = true;
		Robot::gear->SetCurrentCommand(new GearVisionScan(m_targetX));
		return;
	}
	//Creates the empty objects we will use to store object data
	Pixy::ObjectValues trackedObj1;
	Pixy::ObjectValues trackedObj2;
	Pixy::ObjectValues trackedObj3;
	Pixy::ObjectValues combinedObj;
	//Creating the empty doubles for different values
	//heightSame is the check to see if the objects have the relatively same height in pixels
	//heightSame defaults to false so that it won't drive unless it becomes true
	bool heightSame = false;
	//ySame is the check to see if the objects have the relatively same center y-coordinate in pixels
	//ySame defaults to false so that it won't drive unless it becomes true
	bool ySame = false;
	//centerX is the centerX pixel between the two objects
	//centerX defaults to 159 because it is the centerX pixel of the image
	double centerX = 159;
	if(RobotMap::gearPixy->GetFrameSize() == 2) {
		trackedObj1 = Robot::gear->GetObjectData(0).GetValue();
		trackedObj2 = Robot::gear->GetObjectData(1).GetValue();
		centerX = CenterXFinder(trackedObj1.x, trackedObj2.x);
		heightSame = IsHeightSame(trackedObj1.height, trackedObj2.height, 5);
		ySame = IsYSame(trackedObj1.y, trackedObj2.y, 5);
		if(heightSame == true && ySame == true) {
			TurnDirection(m_targetX, centerX);
		}
	} else if(RobotMap::gearPixy->GetFrameSize() > 2) {
		for(int i = 0; i < RobotMap::gearPixy->GetFrameSize(); i++) {
			if(i == 0) {
				trackedObj1 = Robot::gear->GetObjectData(0).GetValue();
			} else if(i == 1) {
				trackedObj2 = Robot::gear->GetObjectData(1).GetValue();
				centerX = CenterXFinder(trackedObj1.x, trackedObj2.x);
				heightSame = IsHeightSame(trackedObj1.height, trackedObj2.height, 5);
				ySame = IsYSame(trackedObj1.y, trackedObj2.y, 5);
				if(heightSame == true && ySame == true) {
					TurnDirection(m_targetX, centerX);
				}
			} else if(i == 2) {
				trackedObj3 = Robot::gear->GetObjectData(2).GetValue();
				if(Robot::drivetrain->IsWithinThreshold(trackedObj1.x, trackedObj2.x, 10)) {
					combinedObj.x = trackedObj2.x;
					centerX = CenterXFinder(combinedObj.x, trackedObj3.x);
					combinedObj.height = trackedObj1.height + trackedObj2.height;
					heightSame = IsHeightSame(combinedObj.height, trackedObj3.height, 5);
					ySame = IsYSame(trackedObj1.y, trackedObj2.y, 5);
					if(heightSame == true && ySame == true) {
						TurnDirection(m_targetX, centerX);
					}
				} else if(Robot::drivetrain->IsWithinThreshold(trackedObj1.x, trackedObj3.x, 10)) {
					combinedObj.x = trackedObj3.x;
					centerX = CenterXFinder(combinedObj.x, trackedObj2.x);
					combinedObj.height = trackedObj1.height + trackedObj3.height;
					heightSame = IsHeightSame(combinedObj.height, trackedObj2.height, 5);
					ySame = IsYSame(trackedObj1.y, trackedObj3.y, 5);
					if(heightSame == true && ySame == true) {
						TurnDirection(m_targetX, centerX);
					}
				} else if(Robot::drivetrain->IsWithinThreshold(trackedObj2.x, trackedObj3.x, 10)) {
					combinedObj.x = trackedObj2.x;
					centerX = CenterXFinder(combinedObj.x, trackedObj1.x);
					combinedObj.height = trackedObj2.height + trackedObj3.height;
					heightSame = IsHeightSame(combinedObj.height, trackedObj1.height, 5);
					ySame = IsYSame(trackedObj2.y, trackedObj3.y, 5);
					if(heightSame == true && ySame == true) {
						TurnDirection(m_targetX, centerX);
					}
				}
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool GearVisionTurn::IsFinished() {
	return isFinished;
}

// Called once after isFinished returns true
void GearVisionTurn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void GearVisionTurn::Interrupted() {

}

int GearVisionTurn::CenterXFinder(double obj1, double obj2) {
	int centerX = obj1;
	int xDiff = abs(obj1 - obj2);
	if (obj1 > obj2) {
		centerX = obj1 - xDiff;
	} else if (obj2 > obj1) {
		centerX = obj2 - xDiff;
	}
	return centerX;
}

int GearVisionTurn::CenterYFinder(double obj1, double obj2) {
	int centerY = obj1;
	int yDiff = abs(obj1 - obj2);
	if (obj1 > obj2) {
		centerY = obj1 - yDiff;
	} else if (obj2 > obj1) {
		centerY = obj2 - yDiff;
	}
	return centerY;
}

bool GearVisionTurn::IsHeightSame(double obj1, double obj2, double threshold) {
	//Checks if the two objects inputed have relatively same height in pixels
	return Robot::drivetrain->IsWithinThreshold(obj1, obj2, threshold);
}

bool GearVisionTurn::IsYSame(double obj1, double obj2, double threshold) {
	//Checks if the two objects inputed have relatively same y-coordinate
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
		isFinished = true;
		Robot::drivetrain->DriveRobotTank(0.0, 0.0);
	}
}
