#include "ShooterVisionScan.h"
#include "ShooterVisionTrack.h"
#include "../Robot.h"
#include "../Subsystems/Shooter.h"

ShooterVisionScan::ShooterVisionScan() {
	Requires(Robot::shooter.get());
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	speed = 0.15;
}

// Called just before this Command runs the first time
void ShooterVisionScan::Initialize() {
	//Robot::shooter->SetSwivelSpeed(speed);
}

// Called repeatedly when this Command is scheduled to run
void ShooterVisionScan::Execute() {
	/*if (Robot::shooter->IsLeftLimitSwitchPressed() || RobotMap::shooterTurretSwivelEncoder->GetDistance() < -Robot::shooter->maxEncPosition||
			Robot::shooter->IsRightLimitSwitchPressed() || RobotMap::shooterTurretSwivelEncoder->GetDistance() > Robot::shooter->maxEncPosition) {
		speed = -speed; //reverse the speed

	}*/
	std::cout << "nothing is on screen, scanning" << std::endl;
	//Robot::shooter->SetSwivelSpeed(speed);

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterVisionScan::IsFinished() {
	std::vector<PixySubsystem::ObjectValues> ob = Robot::pixySubsystem->GetShooterPixyData();
	std::cout << ob.size() << " . " << ob[0].signature << " true:" << (ob.size() > 0) << std::endl;
	return ob.size() > 0;
}

// Called once after isFinished returns true
void ShooterVisionScan::End() {
	std::cout << "ended" << std::endl;
	(new ShooterVisionTrack)->Start();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterVisionScan::Interrupted() {

}
