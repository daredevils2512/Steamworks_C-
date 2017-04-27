#ifndef ConditionallyReleaseGear_H
#define ConditionallyReleaseGear_H

#include "../CommandBase.h"

class ConditionallyReleaseGear : public CommandBase {
public:
	ConditionallyReleaseGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ConditionallyReleaseGear_H
