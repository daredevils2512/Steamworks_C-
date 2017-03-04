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
	targetAcquired = false;
	abort = false;
	numberOfNegOne = 0;
}

// Called repeatedly when this Command is scheduled to run
void GearVisionTurn::Execute() {
	//Gets the frame data from the GearPixy so we can use it
	double targetX = Robot::pixySubsystem->GetGearPixyData();
	if(targetX == -1) {
		numberOfNegOne++;
		if(numberOfNegOne >= 20) {
			abort = true;
			std::cout << "gear tracking aborted" << std::endl;
		}
	}else{
		TrackObject(targetX);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool GearVisionTurn::IsFinished() {
	return targetAcquired || IsTimedOut() || abort;
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
	int tolerance = 30;
	int slowDownTolerance = 100;
	if(goalPixel-(tolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
		Robot::drivetrain->DriveRobotTank(0.0, 0.0);
		std::cout << "Gear target acquired" << std::endl;
		targetAcquired = true;
	}else if(objectX < goalPixel) {
		if(goalPixel - (slowDownTolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
			Robot::drivetrain->DriveRobotTank(-0.4, 0.4);
		}else{
			Robot::drivetrain->DriveRobotTank(-0.7, 0.7);
		}
		std::cout << "-" << std::endl;
	}else{
		if(goalPixel - (slowDownTolerance/2) <= objectX && objectX <= goalPixel + (tolerance/2)) {
			Robot::drivetrain->DriveRobotTank(0.4, -0.4);
		}else{
			Robot::drivetrain->DriveRobotTank(0.7, -0.7);
		}
		std::cout << "+" << std::endl;
	}
}
