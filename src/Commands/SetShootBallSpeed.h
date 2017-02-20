#ifndef SetShootBallSpeed_H
#define SetShootBallSpeed_H

#include "../CommandBase.h"

class SetShootBallSpeed : public CommandBase {
public:
	SetShootBallSpeed(double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_speed;
};

#endif  // SetShootBallSpeed_H
