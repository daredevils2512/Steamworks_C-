#ifndef AutoStraightDrive_H
#define AutoStraightDrive_H

#include "../CommandBase.h"

class AutoStraightDrive : public CommandBase {
public:
	AutoStraightDrive(double targetFeet, double speed);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private:
	double m_targetFeet;
	double m_speed;
};

#endif  // AutoStraightDrive_H
