#ifndef ShooterPOVHoodControl_H
#define ShooterPOVHoodControl_H

#include "../CommandBase.h"

class ShooterPOVHoodControl : public CommandBase {
public:
	ShooterPOVHoodControl();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShooterPOVHoodControl_H
