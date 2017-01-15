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
	std::shared_ptr<RobotDrive> Chassis;
	std::shared_ptr<Encoder> LeftEncoder;
	std::shared_ptr<Encoder> RightEncoder;
	std::shared_ptr<DoubleSolenoid> DriveTrainShift;
public:
	Drivetrain();
	void InitDefaultCommand();
	void DriveRobot(double move, double turn);
	void Shift (bool dir);
	void GetEncoders();
	void ResetEncoders();
	void SetAutonomous();
	bool GetAutonomous();

};

#endif
