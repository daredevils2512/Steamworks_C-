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
	std::shared_ptr<DoubleSolenoid> DriveTrainShift;


	//Declaring all of the functions the Drivetrain subsystem can do
public:

	struct Speeds {
		double leftSpeed;
		double rightSpeed;
	};

	enum class Direction {
		clockwise,
		counterClockwise,
		straight
	};

	Drivetrain();
	void InitDefaultCommand();
	void DriveRobot(double move, double turn);
	void Shifter (frc::DoubleSolenoid::Value dir);
	double GetEncoders();
	Speeds AutoCalcSpeeds(double radius, double outerSpeed, Direction direction);
	void AutoSetSpeeds(Speeds theSpeeds);
	void TurnDirection(double m_targetX ,double scenterX);

};

#endif
