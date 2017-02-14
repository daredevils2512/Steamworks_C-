#ifndef AutoDrive_H
#define AutoDrive_H

#include <CMATH>

#include "../CommandBase.h"
#include "../Subsystems/Drivetrain.h"
#include "../Robot.h"

class AutoDrive : public CommandBase {
private:
	struct Speeds {
		double leftSpeed;
		double rightSpeed;
	};

	double m_leftSpeed;
	double m_rightSpeed;
	double m_targetFeet;
	Drivetrain::Direction  m_direction;

public:
	AutoDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double targetFeet);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	Speeds AutoCalcSpeeds(double radius, double outerSpeed, Drivetrain::Direction direction);
	void CircleDegreeDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double percentCircle);

};

#endif  // AutoDrive_H
