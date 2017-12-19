#ifndef AutoCircleDrive_H
#define AutoCircleDrive_H

#include <CMATH>

#include "../CommandBase.h"
#include "../Subsystems/Drivetrain.h"
#include "../Robot.h"

class AutoCircleDrive : public CommandBase {
private:
	//a struct of speeds for both sides of the robot
	struct Speeds {
		double leftSpeed;
		double rightSpeed;
	};

	//the variables used to store the inputed speeds
	double m_leftSpeed;
	double m_rightSpeed;
	double m_degrees;
	double m_radius;
	Drivetrain::Direction  m_direction;

public:
	//the functions for the command
	AutoCircleDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double degrees);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	Speeds AutoCalcSpeeds(double radius, double outerSpeed, Drivetrain::Direction direction);
	void CircleDegreeDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double percentCircle);

};

#endif  // AutoDrive_H
