#ifndef GearVisionTurn_H
#define GearVisionTurn_H

#include <CMATH>

#include "../CommandBase.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "../Subsystems/Gear.h"
#include "../Subsystems/Drivetrain.h"
#include "../Subsystems/PixySubsystem.h"

class GearVisionTurn : public CommandBase {
public:
	GearVisionTurn(double targetX);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
	int CenterXFinder(double obj1, double obj2, double xDiff);
	int CenterYFinder(double obj1, double obj2);
	bool IsHeightSame(double obj1, double obj2, double threshold);
	bool IsYSame(double obj1, double obj2, double threshold);
	void TurnDirection(double m_targetX , double centerX);
	void TrackObject(double objectX);

private:
	double m_targetX;
	bool targetAcquired;
	bool abort;
	int goalPixel;
	int numberOfNegOne;
};

#endif  // GearVisionTurn_H
