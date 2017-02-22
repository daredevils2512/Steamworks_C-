#ifndef ShooterSwivelMoveToPosition_H
#define ShooterSwivelMoveToPosition_H

#include "../CommandBase.h"

class ShooterSwivelMoveToPosition : public CommandBase {
public:
	ShooterSwivelMoveToPosition(double position);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_position;
	bool onTarget;
};

#endif  // ShooterSwivelMoveToPosition_H
