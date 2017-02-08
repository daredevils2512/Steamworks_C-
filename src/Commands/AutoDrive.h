#ifndef AutoDrive_H
#define AutoDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Drivetrain.h"
#include "../Robot.h"

class AutoDrive : public CommandBase {
public:
	AutoDrive(double radius, double outerSpeed, Drivetrain::Direction direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_radius;
	double m_outerSpeed;
	Drivetrain::Direction m_direction;
	double m_leftSpeed;
	double m_rightSpeed;
};

#endif  // AutoDrive_H
