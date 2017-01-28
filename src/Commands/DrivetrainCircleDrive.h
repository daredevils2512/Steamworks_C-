#ifndef DrivetrainCircleDrive_H
#define DrivetrainCircleDrive_H

#include "../CommandBase.h"
#include "../Subsystems/Drivetrain.h"
#include "../Robot.h"

class DrivetrainCircleDrive : public CommandBase {
public:
	DrivetrainCircleDrive(double actualRadius, bool direction, double distance, double outerVelocity);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	//Declaring the members in private
	double m_actualRadius;
	bool m_direction;
	double m_distance;
	double m_outerVelocity;

};

#endif  // DrivetrainCircleDrive_H
