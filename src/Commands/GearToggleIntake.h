#ifndef GearToggleIntake_H
#define GearToggleIntake_H

#include "../CommandBase.h"

class GearToggleIntake : public CommandBase {
public:
	GearToggleIntake();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // GearToggleIntake_H
