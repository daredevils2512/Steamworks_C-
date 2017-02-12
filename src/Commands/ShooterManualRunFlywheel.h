#ifndef ShooterManualRunFlywheel_H
#define ShooterManualRunFlywheel_H

#include "../CommandBase.h"

class ShooterManualRunFlywheel : public CommandBase {
public:
	ShooterManualRunFlywheel();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShooterManualRunFlywheel_H
