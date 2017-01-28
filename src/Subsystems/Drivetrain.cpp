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

void Drivetrain::DriveCircle(double actualRadius, bool direction, double distance, double outerVelocity) {
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
	double pi = 3.1415;
	double innerVelocity;
	double time;

	//Using all the numbers inputed and created above to figure out the circumference of all three circles
	//Middle of the robot, outer wheels, and inner wheels
	radiusInches = actualRadius * 12;
	innerRadius = radiusInches - 11.5;
	outerRadius = radiusInches + 11.5;
	outerCircumference = 2 * pi * outerRadius;
	outerCirclePercent = outerCircumference / distance;
	innerCircumference = 2 * pi * innerRadius;
	innerCirclePercent = innerCircumference / distance;
	//Figuring out how long it will take the outside wheels to complete the portion of the circle at the inputed velocity
	time = outerCirclePercent / outerVelocity;
	//Using the time figured out above to determine what velocity to set the inner wheels at
	innerVelocity = innerCirclePercent / time;

	//uses the boolean direction to determine which way to turn. True = left, False = right
	//And sets the outer side to the velocity inputed and the inner side to the velocity we found
	//Sets the control mode for the TalonSRX's to kSpeed for PID
	if (direction == true) {
		RearRightMotor->SetControlMode(CANSpeedController::kSpeed);
		RearRightMotor->Set(outerVelocity);
		RearLeftMotor->SetControlMode(CANSpeedController::kSpeed);
		RearLeftMotor->Set(innerVelocity);
	} else {
		RearRightMotor->SetControlMode(CANSpeedController::kSpeed);
		RearLeftMotor->Set(outerVelocity);
		RearLeftMotor->SetControlMode(CANSpeedController::kSpeed);
		RearRightMotor->Set(innerVelocity);
	}
}
