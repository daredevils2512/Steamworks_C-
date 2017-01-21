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

	SetDefaultCommand(new Drive());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Drivetrain::DriveRobot(double move, double turn) {
	//drives robot in tank mode from specified values
	Chassis->TankDrive(move, turn, false);
}

void Drivetrain::Shifter(DoubleSolenoid::Value dir) {
	//sets the direction of the shifter solenoid
	DriveTrainShift->Set(dir);
}

void Drivetrain::GetEncoders(double distance) {
	//gets distance moved since last reset scaled by distance per pulse
	LeftEncoder->GetDistance();
	RightEncoder->GetDistance();
}

void Drivetrain::ResetEncoders() {
	//resets the drivetrain encoder values
	LeftEncoder->Reset();
	RightEncoder->Reset();
}
