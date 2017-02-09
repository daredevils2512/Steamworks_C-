#include <cmath>

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

    Chassis = RobotMap::drivetrainChassis;
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

void Drivetrain::DriveRobotArcade(double move, double turn) {
	//drives robot in arcade mode from specified values (TELEOP)
	Right->SetControlMode(frc::CANSpeedController::kPercentVbus);
	Left->SetControlMode(frc::CANSpeedController::kPercentVbus);
	Chassis->ArcadeDrive(move, turn, false); //remove the boolean
}

void Drivetrain::DriveRobotTank(double leftSide, double rightSide) {
	//Needed for the auton driving
	Right->SetControlMode(frc::CANSpeedController::kPercentVbus);
	Left->SetControlMode(frc::CANSpeedController::kPercentVbus);
	Chassis->TankDrive(leftSide, rightSide);
}

void Drivetrain::Shifter(frc::DoubleSolenoid::Value dir) {
	//sets the direction of the shifter solenoid
	DriveTrainShift->Set(dir);
}

double Drivetrain::GetEncoders() {
	//gets distance moved since last reset scaled by distance per pulse
	return ((Left->GetEncPosition() + Right->GetEncPosition()) / 2) * 0.0981747704246;
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

void Drivetrain::TurnDirection(double m_targetX , double centerX){
	double error = centerX - m_targetX;
	error = error * 0.005;
	if (error > 0.5) {
		error = 0.5;
	} else if (error < -0.5){
		error = -0.5;
	}
	if(IsWithinThreshold(m_targetX, centerX, 5)) {
		DriveRobotTank(0.5, 0.0);
	} else if(centerX != m_targetX) {
		DriveRobotTank(0.0, error);
	} else {
		DriveRobotTank(0.0, 0.0);
	}
}

bool Drivetrain::IsWithinThreshold(double obj1X, double obj2X, int threshold){
	int tol = threshold / 2;
	return (obj1X - tol <= obj2X && obj1X + tol >= obj2X) && (obj2X - tol <= obj1X && obj2X + tol >= obj1X);
}
