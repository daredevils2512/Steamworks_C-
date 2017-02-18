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
	std::shared_ptr<frc::Encoder> leftEncoder;
	std::shared_ptr<frc::Encoder> rightEncoder;

	//Declaring all of the functions the Drivetrain subsystem can do
public:
	Drivetrain();
	void InitDefaultCommand();
	void DriveRobotArcade(double move, double turn);
	void DriveRobotTank(double leftSide, double rightSide);
	void Shifter (frc::DoubleSolenoid::Value dir);
	double GetLeftEncoder();
	double GetRightEncoder();
	void ResetEncoders();
	void TurnDirection(double m_targetX , double centerX);
	bool IsWithinThreshold(double obj1X, double obj2X, int threshold);

	enum class Direction {
		clockwise,
		counterClockwise,
		straight
	};

};

#endif
