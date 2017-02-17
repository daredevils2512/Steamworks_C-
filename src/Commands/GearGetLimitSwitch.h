#ifndef GearGetLimitSwitch_H
#define GearGetLimitSwitch_H

#include "../CommandBase.h"


class GearGetLimitSwitch : public CommandBase {
public:
	GearGetLimitSwitch();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // GearGetLimitSwitch_H
