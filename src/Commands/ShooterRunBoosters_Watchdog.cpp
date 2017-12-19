#include "ShooterRunBoosters_Watchdog.h"
#include "RobotMap.h"

ShooterRunBoosters_Watchdog::ShooterRunBoosters_Watchdog(double speed) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	m_speed = speed;
}

// Called just before this Command runs the first time
void ShooterRunBoosters_Watchdog::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterRunBoosters_Watchdog::Execute() {
	//turns on the boosters for the shooter unless the shooter RPM is 25 RPM lower than it's setpoint
	if(Robot::shooter->lastSetFlywheel-25 > RobotMap::shooterFlywheel->GetSpeed()){
		Robot::shooter->SetBoosterSpeed(0);
	}else{
		Robot::shooter->SetBoosterSpeed(m_speed);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterRunBoosters_Watchdog::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterRunBoosters_Watchdog::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterRunBoosters_Watchdog::Interrupted() {

}
