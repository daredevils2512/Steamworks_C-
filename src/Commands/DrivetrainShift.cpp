#include "DrivetrainShift.h"
#include "Robot.h"

DrivetrainShift::DrivetrainShift(bool Direction) {
	m_Direction = Direction;
}

void DrivetrainShift::Initialize() {
	SetInterruptible(false);
	SetTimeout(0.1);
	//stops the drivetrain
	Robot::drivetrain->DriveRobot(0.0 , 0.0);
}

void DrivetrainShift::Execute() {
if (m_Direction) {
	//waits for a small amount of time then shifts up
	Wait (0.1);
	Robot::drivetrain->Shifter(DoubleSolenoid::kForward);
}
else {
	//waits for a small amount of time then shifts down
	Wait (0.1);
	Robot::drivetrain->Shifter(DoubleSolenoid::kReverse);
}

}

bool DrivetrainShift::IsFinished() {
	return false;
}

void DrivetrainShift::End() {

}

void DrivetrainShift::Interrupted() {

}
