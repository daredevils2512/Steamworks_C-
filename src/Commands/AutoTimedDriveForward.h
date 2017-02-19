#ifndef AutoTimedDriveForward_H
#define AutoTimedDriveForward_H

#include "../CommandBase.h"

class AutoTimedDriveForward : public CommandBase {
public:
	AutoTimedDriveForward(double time);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoTimedDriveForward_H
