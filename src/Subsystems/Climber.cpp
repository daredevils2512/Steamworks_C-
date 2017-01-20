#include "Climber.h"
#include "../RobotMap.h"

Climber::Climber() : Subsystem("Climber") {
	climberMotor = RobotMap::climberMotor;
}

void Climber::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Climber::SetSpeed(double speed) {
	//sets speed of the climber motor
	climberMotor->Set(speed);
}
