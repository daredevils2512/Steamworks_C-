#ifndef AutoDimeSpin_H
#define AutoDimeSpin_H

#include "../CommandBase.h"
#include "../Robot.h"
#include "../Subsystems/Drivetrain.h"

class AutoDimeSpin : public CommandBase {
public:
	AutoDimeSpin(double speed, double turnDistance, Drivetrain::Direction direction);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_speed;
	double m_turnDistance;
	Drivetrain::Direction m_direction;
};

#endif  // AutoDimeSpin_H
