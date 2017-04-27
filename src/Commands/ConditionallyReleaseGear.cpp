#include "ConditionallyReleaseGear.h"
#include "Robot.h"

ConditionallyReleaseGear::ConditionallyReleaseGear() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ConditionallyReleaseGear::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ConditionallyReleaseGear::Execute() {
	if(Robot::gear->GetReleaseLimitSwitch()){
		std::cout << "Eject" << std::endl;
		Robot::gear->ActuateGearRelease(frc::DoubleSolenoid::kForward);
	}else{
		std::cout << "Retract" << std::endl;
		Robot::gear->ActuateGearRelease(frc::DoubleSolenoid::kReverse);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ConditionallyReleaseGear::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ConditionallyReleaseGear::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ConditionallyReleaseGear::Interrupted() {

}
