#ifndef AutoPercentCircleDrive_H
#define AutoPercentCircleDrive_H

#include <CMATH>

#include "../CommandBase.h"
#include "../Subsystems/Drivetrain.h"
#include "AutoDrive.h"

class AutoPercentCircleDrive : public CommandBase {
private:

	double m_radius;
	double m_outerSpeed;
	double m_percentCircle;
	Drivetrain::Direction m_direction;

public:
	AutoPercentCircleDrive(double radius, double outerSpeed, Drivetrain::Direction direction, double percentCircle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoPercentCircleDrive_H
