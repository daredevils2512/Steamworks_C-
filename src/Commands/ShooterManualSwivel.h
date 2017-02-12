#ifndef ShooterManualSwivel_H
#define ShooterManualSwivel_H

#include "../CommandBase.h"

class ShooterManualSwivel : public CommandBase {
public:
	ShooterManualSwivel();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ShooterManualSwivel_H
