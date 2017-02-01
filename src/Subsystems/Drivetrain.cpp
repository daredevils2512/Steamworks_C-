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
Drivetrain::Speeds Drivetrain::CircleSpeed(double radius, double outerSpeed, Direction direction){
	Speeds theSpeeds;
	int width = 27;
	double innerSpeed = ((radius - width / 2) / (radius + width/2) * outerSpeed);
	if(direction == Direction::clockwise){
		theSpeeds.left = outerSpeed;
		theSpeeds.right = innerSpeed;
	}else if(direction == Direction::counterClockwise){
		theSpeeds.left = innerSpeed;
		theSpeeds.right = outerSpeed;
	}else{
		theSpeeds.left = outerSpeed;
		theSpeeds.right = outerSpeed;
	}
	return theSpeeds;
}

void Drivetrain::SetSpeeds(Speeds theSpeeds){

}

void Drivetrain::DriveCircle(double actualRadius, Drivetrain::Direction direction, double distance, double outerVelocity) {
	//takes the radius of a circle and makes the robot drive it
	//sets velocity of both sides V=d/t, t=d/V

	//All our important doubles
	double innerRadius;
	double outerRadius;
	double radiusInches;
	double outerCircumference;
	double outerCirclePercent;
	double innerCircumference;
	double innerCirclePercent;
	double innerVelocity;
	double time;

	//Using all the numbers inputed and created above to figure out the circumference of all three circles
	//Middle of the robot, outer wheels, and inner wheels
	radiusInches = actualRadius * 12;
	innerRadius = radiusInches - 11.5;
	outerRadius = radiusInches + 11.5;
	outerCircumference = 2 * M_PI * outerRadius;
	outerCirclePercent = outerCircumference / distance;
	innerCircumference = 2 * M_PI * innerRadius;
	innerCirclePercent = innerCircumference / distance;
	//Figuring out how long it will take the outside wheels to complete the portion of the circle at the inputed velocity
	time = outerCirclePercent / outerVelocity;
	//Using the time figured out above to determine what velocity to set the inner wheels at
	innerVelocity = innerCirclePercent / time;

	//uses the enum Direction to determine which way to turn
	//And sets the outer side to the velocity inputed and the inner side to the velocity we found
	//Sets the control mode for the TalonSRX's to kSpeed for PID
	if (direction == Direction::clockwise) {
		RearRightMotor->SetControlMode(CANSpeedController::kSpeed);
		RearRightMotor->Set(outerVelocity);
		RearLeftMotor->SetControlMode(CANSpeedController::kSpeed);
		RearLeftMotor->Set(innerVelocity);
	} else if (direction == Direction::counterClockwise) {
		RearRightMotor->SetControlMode(CANSpeedController::kSpeed);
		RearLeftMotor->Set(outerVelocity);
		RearLeftMotor->SetControlMode(CANSpeedController::kSpeed);
		RearRightMotor->Set(innerVelocity);
	}
}
