#include "ShooterSwivelMoveToPosition.h"
#include "../Robot.h"

ShooterSwivelMoveToPosition::ShooterSwivelMoveToPosition(double position) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_position = position;
	onTarget = false;
}

// Called just before this Command runs the first time
void ShooterSwivelMoveToPosition::Initialize() {
	onTarget = false;
	std::cout << "initialize" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void ShooterSwivelMoveToPosition::Execute() {
	int tolerance = 75;
	int slowDownTolerance = 2000;
	double currentPosition = Robot::shooter->GetSwivelPosition();
	if(m_position-(tolerance/2) <= currentPosition && currentPosition <= m_position + (tolerance/2)) {
		Robot::shooter->SetSwivelSpeed(0.0);
		onTarget = true;
		std::cout << m_position << std::endl;
		std::cout << currentPosition << std::endl;
		std::cout << "on target" << std::endl;
	}else if(currentPosition < m_position) {
		if(m_position-(slowDownTolerance/2) <= currentPosition && currentPosition <= m_position + (slowDownTolerance/2)) {
			Robot::shooter->SetSwivelSpeed(0.1);
			std::cout << "slow" << std::endl;
		}else{
			Robot::shooter->SetSwivelSpeed(0.4);
		}
		std::cout << "+" << std::endl;
	}else {
		if(m_position-(slowDownTolerance/2) <= currentPosition && currentPosition <= m_position + (slowDownTolerance/2)) {
			Robot::shooter->SetSwivelSpeed(-0.1);
			std::cout << "slow" << std::endl;
		}else{
			Robot::shooter->SetSwivelSpeed(-0.4);
		}
		std::cout << "-" << std::endl;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterSwivelMoveToPosition::IsFinished() {
	return onTarget;
}

// Called once after isFinished returns true
void ShooterSwivelMoveToPosition::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterSwivelMoveToPosition::Interrupted() {

}
