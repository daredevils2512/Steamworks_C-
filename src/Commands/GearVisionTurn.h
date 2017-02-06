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
	GearVisionTurn(int targetX);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	bool IsWithinThreshold(int obj1X, int obj2X, int threshold);
	int CenterXFinder(int obj1, int obj2, int xDiff);

private:
	double m_targetX;
};

#endif  // GearVisionTurn_H
