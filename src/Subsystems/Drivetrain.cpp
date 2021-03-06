#include <cmath>

#include "Drivetrain.h"
#include "../RobotMap.h"
#include "../Commands/Drive.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain") {

    Chassis = RobotMap::drivetrainChassis;
    DriveTrainShift = RobotMap::drivetrainShift;

    Right = RobotMap::drivetrainRearRightMotor;
    Left = RobotMap::drivetrainRearLeftMotor;

    leftEncoder = RobotMap::drivetrainLeftEncoder;
    rightEncoder = RobotMap::drivetrainRightEncoder;

    blockJoysticks = false;

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

double Drivetrain::GetLeftEncoder() {
	//gets distance moved since last reset scaled by distance per pulse
	return leftEncoder->GetDistance();
}

double Drivetrain::GetRightEncoder() {
	//gets distance moved since last reset scaled by distance per pulse
	return rightEncoder->GetDistance();
}


void Drivetrain::ResetEncoders() {
	//resets the drivetrain encoder values
	leftEncoder->Reset();
	rightEncoder->Reset();
}

void Drivetrain::TurnDirection(double m_targetX , double centerX){
	//determining which direction to turn for vision turning
	double error = centerX - m_targetX;
	error = error * 0.005;
	if (error > 0.5) {
		error = 0.5;
	} else if (error < -0.5) {
		error = -0.5;
	}
	if (IsWithinThreshold(m_targetX, centerX, 5)) {
		DriveRobotTank(0.5, 0.0);
	} else if (centerX != m_targetX) {
		DriveRobotTank(0.0, error);
	} else {
		DriveRobotTank(0.0, 0.0);
	}
}

bool Drivetrain::IsWithinThreshold(double obj1X, double obj2X, int threshold){
	//determining if two objects are within a certain range of each other
	int tol = threshold / 2;
	return (obj1X - tol <= obj2X && obj1X + tol >= obj2X) && (obj2X - tol <= obj1X && obj2X + tol >= obj1X);
}

void Drivetrain::SetAutonomous(bool isAutonomous) {
	blockJoysticks = isAutonomous;
}

bool Drivetrain::GetAutonomous() {
	return blockJoysticks;
}
