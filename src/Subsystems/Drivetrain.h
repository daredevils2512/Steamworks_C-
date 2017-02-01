#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Drivetrain: public Subsystem {
private:
	std::shared_ptr<CANTalon> FrontLeftMotor;
	std::shared_ptr<CANTalon> RearLeftMotor;
	std::shared_ptr<CANTalon> FrontRightMotor;
	std::shared_ptr<CANTalon> RearRightMotor;

	//creating two master references
	std::shared_ptr<CANTalon> Right;
	std::shared_ptr<CANTalon> Left;

	std::shared_ptr<RobotDrive> Chassis;
	std::shared_ptr<Encoder> LeftEncoder;
	std::shared_ptr<Encoder> RightEncoder;
	std::shared_ptr<DoubleSolenoid> DriveTrainShift;


	//Declaring all of the functions the Drivetrain subsystem can do
public:

	struct Speeds {
		double left;
		double right;
	};
	enum class Direction {
		clockwise,
		counterClockwise,
		straight
	};

	Drivetrain();
	void InitDefaultCommand();
	void DriveRobot(double move, double turn);
	void Shifter (DoubleSolenoid::Value dir);
	void GetEncoders(double distance);
	void ResetEncoders();
	void SetAutonomous();
	void DriveCircle(double actualRadius, Direction direction, double distance, double outerVelocity);
	bool GetAutonomous();
	Speeds CircleSpeed(double radius, double outerSpeed, Direction direction);
	void SetSpeeds(Speeds theSpeeds);
};

#endif
