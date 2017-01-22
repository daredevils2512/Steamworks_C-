#include "FloorIntake.h"
#include "../RobotMap.h"

//declares what intakeMotor is
FloorIntake::FloorIntake() : Subsystem("FloorIntake") {
	intakeMotor = RobotMap::intakeMotor;

}


void FloorIntake::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

//sets intakeMotor speed to double speed
void FloorIntake::SetSpeed(double speed) {
	intakeMotor->Set(speed);
}
