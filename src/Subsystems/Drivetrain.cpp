#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"
#include "CANTalon.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

    FrontLeftMotor = RobotMap::drivetrainFrontLeftMotor;
    RearLeftMotor = RobotMap::drivetrainRearLeftMotor;
    FrontRightMotor = RobotMap::drivetrainFrontRightMotor;
    RearRightMotor = RobotMap::drivetrainRearRightMotor;
    Chassis = RobotMap::drivetrainChassis;
    LeftEncoder = RobotMap::drivetrainLeftEncoder;
    RightEncoder = RobotMap::drivetrainRightEncoder;
    DriveTrainShift = RobotMap::drivetrainShift;
}

void Drivetrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

	SetDefaultCommand(new Drive(0 , 0));
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::DriveRobot(double move, double turn) {
	Chassis->TankDrive(move, turn, false);
}
void Drivetrain::Shift(bool dir) {

}

void Drivetrain::GetEncoders() {
	LeftEncoder->Get();
	RightEncoder->Get();
}

void Drivetrain::ResetEncoders() {
	LeftEncoder->Reset();
	RightEncoder->Reset();
}

