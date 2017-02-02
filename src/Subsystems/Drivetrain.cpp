#include <cmath>

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"
#include "CANTalon.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

    Chassis = RobotMap::drivetrainChassis;
    LeftEncoder = RobotMap::drivetrainLeftEncoder;
    RightEncoder = RobotMap::drivetrainRightEncoder;
    DriveTrainShift = RobotMap::drivetrainShift;

    Right = RobotMap::drivetrainRearRightMotor;
    Left = RobotMap::drivetrainRearLeftMotor;

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
//distance = inches
//speed = inches per seconds
Drivetrain::Speeds Drivetrain::AutoCalcSpeeds(double radius, double outerSpeed, Direction direction){
	Speeds theSpeeds;
	int width = 27;
	double innerSpeed = ((radius - width / 2) / (radius + width/2) * outerSpeed);
	if(direction == Direction::clockwise){
		theSpeeds.leftSpeed = outerSpeed;
		theSpeeds.rightSpeed = innerSpeed;
	}else if(direction == Direction::counterClockwise){
		theSpeeds.leftSpeed = innerSpeed;
		theSpeeds.rightSpeed = outerSpeed;
	}else{
		theSpeeds.leftSpeed = outerSpeed;
		theSpeeds.rightSpeed = outerSpeed;
	}
	return theSpeeds;
}

void Drivetrain::AutoSetSpeeds(Drivetrain::Speeds theSpeeds){
	Left -> Set(theSpeeds.leftSpeed);
	Right -> Set(theSpeeds.rightSpeed);
}
