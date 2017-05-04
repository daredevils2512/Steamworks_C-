#ifndef ClimberDisableCurrentLimit_H
#define ClimberDisableCurrentLimit_H

#include "../CommandBase.h"

class ClimberDisableCurrentLimit : public CommandBase {
public:
	ClimberDisableCurrentLimit();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ClimberDisableCurrentLimit_H
