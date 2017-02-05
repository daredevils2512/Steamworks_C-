#ifndef GearVisionTurn_H
#define GearVisionTurn_H

#include <CMATH>

#include "../CommandBase.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Pixy.h"
#include "../Subsystems/Gear.h"
#include "../Subsystems/Drivetrain.h"

class GearVisionTurn : public CommandBase {
public:
	GearVisionTurn(double targetX);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	bool GearVisionTurn::IsWithinThreshold(double obj1X, double obj2X, double threshold);

private:
	double m_targetX;
};

#endif  // GearVisionTurn_H
