#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber") {
	//gets a new motor
	climberMotor = RobotMap::climberMotor;
}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Climber::SetSpeed(double speed) {
	//function to set the speed of the climberMotor
	climberMotor->Set(speed);
}
